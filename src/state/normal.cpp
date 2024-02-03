/*
    AIRnemos is a software for CO2 meter.
    Copyright (C) 2023 Quentin Schuster

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "state/normal.h"
#include <HTTPUpdate.h>

namespace StateNormal {

    bool init = true;
    bool isBad = true;

    int16_t i = 0;
    uint16_t measurementsCo2[BUFFER_SIZE];
    float measurementsTemp[BUFFER_SIZE];
    float measurementsHum[BUFFER_SIZE];

    // Tasks
    TaskHandle_t task_led;
    TaskHandle_t task_loop;

    void ledTask(void * parameter) {
        uint8_t brighness;

        for (;;)
        {
            if(init) {
                brighness = beatsin8(10, 50, 255);
                FastLED.showColor(CHSV(160, 255, brighness));
                vTaskDelay(20 / portTICK_PERIOD_MS);
            } else {
                FastLED.showColor(isBad ? Config::colorBad : Config::colorGood);
                vTaskDelay(1000 / portTICK_PERIOD_MS);
            }
        }
    }

    void loopTask(void * parameter) {
        vTaskDelay(250 / portTICK_PERIOD_MS);

        for (;;)
        {
            if (!Sensor::read()) {
                bool beforeBad = isBad;

                if(isBad) {
                    if (Sensor::co2 <= Config::thresholdGood) isBad = false;
                } else {
                    if (Sensor::co2 >= Config::thresholdBad) isBad = true;
                }

                init = false;

                i = i == BUFFER_SIZE - 1 ? 0 : i + 1;
                measurementsCo2[i] = Sensor::co2;
                measurementsTemp[i] = Sensor::temperature;
                measurementsHum[i] = Sensor::humidity;

                if(beforeBad != isBad && Config::buzzer) {
                    if(isBad)
                        Buzzer::high();
                    else
                        Buzzer::low();
                }
            } else {
                i = i == BUFFER_SIZE - 1 ? 0 : i + 1;
                measurementsCo2[i] = 0;
                measurementsTemp[i] = 0;
                measurementsHum[i] = 0;
            }
            vTaskDelay(5000 / portTICK_PERIOD_MS);
        }
    }

    void start() {
        xTaskCreate(ledTask, "LED-Normal", 2048, NULL, 5, &task_led);

        Web::start();

        while (Sensor::read())
        {
            vTaskDelay(250 / portTICK_PERIOD_MS);
        }

        xTaskCreate(loopTask, "LOOP", 4096, NULL, 5, &task_loop);
    }

    void stop() {
        vTaskDelete(task_led);
        vTaskDelete(task_loop);
    }

    // -------------

    AsyncCallbackWebHandler handler_login;

    AsyncCallbackWebHandler handler_info;
    AsyncCallbackWebHandler handler_measure;
    AsyncCallbackWebHandler handler_measure_history;
    AsyncCallbackWebHandler handler_update;

    AsyncCallbackWebHandler handler_config_show;
    AsyncCallbackJsonWebHandler* handler_config_update;

    StaticJsonDocument<512> configDoc;

    void updateTask(void * parameter) {
        for (;;)
        {
            if(!Wifi::isConnected()) {
                vTaskDelay(10 * 60 * 1000 / portTICK_PERIOD_MS);
                return;
            }

            WiFiClient client;
            t_httpUpdate_return ret = httpUpdate.update(client, "https://updateserver.airnemos.de/update", "1.0");

            vTaskDelay(60 * 60 * 1000 / portTICK_PERIOD_MS);
        }
    }

    void _start() {
        
        handler_info = Web::server.on("/api/info", HTTP_GET, [] (AsyncWebServerRequest *request) {
            StaticJsonDocument<384> data;

            data["name"] = Config::name;
            data["red"] = isBad;
            
            JsonObject threshold = data.createNestedObject("threshold");
            threshold["good"] = Config::thresholdGood;
            threshold["bad"] = Config::thresholdBad;

            JsonObject color = data.createNestedObject("color");
            color["bad"] = "#" + colorToString(Config::colorBad);
            color["good"] = "#" + colorToString(Config::colorGood);
            
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            serializeJson(data, *response);
            request->send(response);
        });
        handler_measure_history = Web::server.on("/api/measurement/history", HTTP_GET, [] (AsyncWebServerRequest *request) {
            log_i("measurement history");
            StaticJsonDocument<JSON_ARRAY_SIZE(BUFFER_SIZE + 1) * 3> data;
            JsonArray co2Array = data.createNestedArray("co2");
            JsonArray tempArray = data.createNestedArray("temp");
            JsonArray humArray = data.createNestedArray("hum");

            log_i("%d: %d %d %d %d %d %d", i, measurementsCo2[0], measurementsCo2[1], measurementsCo2[2], measurementsCo2[3], measurementsCo2[4], measurementsCo2[5]);
            
            for (int16_t j = i; j > -1; j--) {
                log_i("1. %d >= 0: %s", j, j >= 0 ? "true" : "false");
                co2Array.add(measurementsCo2[j]);
                tempArray.add(measurementsTemp[j]);
                humArray.add(measurementsHum[j]);
            }

            for (int16_t j = BUFFER_SIZE - 1; j - 1 > i - 1; j--) {
                log_i("2. %d >= %d; %d", j, i, measurementsCo2[j]);
                co2Array.add(measurementsCo2[j]);
                tempArray.add(measurementsTemp[j]);
                humArray.add(measurementsHum[j]);
            }
           
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            serializeJson(data, *response);
            request->send(response);
        });
        handler_measure = Web::server.on("/api/measurement", HTTP_GET, [] (AsyncWebServerRequest *request) {
            log_i("measurement");
            StaticJsonDocument<48> data;

            data["co2"] = Sensor::co2;
            data["hum"] = Sensor::humidity;
            data["temp"] = Sensor::temperature;
            
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            serializeJson(data, *response);
            request->send(response);
        });

        handler_config_show = Web::server.on("/api/config", HTTP_GET, [] (AsyncWebServerRequest *request) {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            Config::get(&configDoc);
            serializeJson(configDoc, *response);
            request->send(response);
            configDoc.clear();
        });
        handler_config_update = new AsyncCallbackJsonWebHandler("/api/config", [](AsyncWebServerRequest *request, JsonVariant &json) {
            JsonObject data = json.as<JsonObject>();
            Config::set(&data);
            Config::save();

            request->send_P(200, "application/json", R"==({"success":true})==");
        });
        handler_config_update->setMethod(HTTP_POST);
        Web::server.addHandler(handler_config_update);

        handler_update = Web::server.on("/api/update", HTTP_POST, [] (AsyncWebServerRequest *request) {
            AsyncResponseStream *response = request->beginResponseStream("application/json");
            response->setCode((Update.hasError())?500:200);
            response->addHeader("Connection", "close");
            response->addHeader("Access-Control-Allow-Origin", "*");

            StaticJsonDocument<48> data;

            data["success"] = Update.hasError() ? false : true;

            if(Update.hasError()) {
                data["msg"] = Update.getError();
            }

            serializeJson(data, *response);
            request->send(response);
           
            if (Update.hasError()) return;

            FastLED.showColor(CRGB::Blue);

            ESP.restart();
        }, [&](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
            if (!index) {
                if(!request->hasParam("MD5", true)) {
                    AsyncResponseStream *response = request->beginResponseStream("application/json");
                    response->setCode(400);

                    StaticJsonDocument<48> data;

                    data["success"] = false;
                    data["msg"] = 13;

                    serializeJson(data, *response);
                    return request->send(response);
                }

                if(!Update.setMD5(request->getParam("MD5", true)->value().c_str())) {
                    AsyncResponseStream *response = request->beginResponseStream("application/json");
                    response->setCode(400);

                    StaticJsonDocument<48> data;

                    data["success"] = false;
                    data["msg"] = 14;

                    serializeJson(data, *response);
                    return request->send(response);
                }

                if (!Update.begin(UPDATE_SIZE_UNKNOWN, U_FLASH)) {
                    AsyncResponseStream *response = request->beginResponseStream("application/json");
                    response->setCode(500);

                    StaticJsonDocument<48> data;

                    data["success"] = false;
                    data["msg"] = Update.getError();

                    serializeJson(data, *response);
                    return request->send(response);
                }
            }

            if(len){
                if (Update.write(data, len) != len) {
                    AsyncResponseStream *response = request->beginResponseStream("application/json");
                    response->setCode(500);

                    StaticJsonDocument<48> data;

                    data["success"] = false;
                    data["msg"] = Update.getError();

                    serializeJson(data, *response);
                    return request->send(response);
                }
            }
                
            if (final) {
                if (!Update.end(true)) {
                    AsyncResponseStream *response = request->beginResponseStream("application/json");
                    response->setCode(500);

                    StaticJsonDocument<48> data;

                    data["success"] = false;
                    data["msg"] = Update.getError();

                    serializeJson(data, *response);
                    return request->send(response);
                }
            }else{
                return;
            }
        });
    }
}