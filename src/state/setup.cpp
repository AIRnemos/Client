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
#include "state/setup.h"

namespace StateSetup {
    
    AsyncWebHandler wifi_scan_hander;
    //AsyncWebHandler wifi_check_handler;
    AsyncWebHandler handler;
    bool init = false;

    TaskHandle_t task_led;

    void ledTask(void * parameter) {
        uint8_t brighness;
        uint8_t hue;

        for (;;)
        {
            brighness = beatsin8(10, 50, 255);
            hue = beatsin8(5, 140, 170);
            FastLED.showColor(CHSV(hue, 255, brighness));
            vTaskDelay(20 / portTICK_PERIOD_MS);
        }
    }

    void start() {
        xTaskCreate(ledTask, "LED-Setup", 2048, NULL, 5, &task_led);

        Wifi::startAP(("AIRnemos - " + Config::defaultName).c_str(), NULL);
        Wifi::startScaning();

        wifi_scan_hander = Web::server.on("/api/wifi/scan", HTTP_GET, [] (AsyncWebServerRequest *request) {
            DynamicJsonDocument result(1024);
            JsonArray array = result.to<JsonArray>();

            Wifi::getWifis(&array);

            AsyncResponseStream *response = request->beginResponseStream("application/json");
            serializeJson(result, *response);
            request->send(response);
        });

        /*wifi_check_handler = Web::server.on("/api/wifi/check", HTTP_POST, [] (AsyncWebServerRequest *request) {
            DynamicJsonDocument bodyJSON(1024);
            deserializeJson(bodyJSON, request->_tempObject);

            request->send(201, "", "");
            
            Wifi::check(bodyJSON["ssid"].as<String>().c_str(), bodyJSON.containsKey("password") ? bodyJSON["password"].as<String>().c_str() : nullptr);
        }, nullptr, [] (AsyncWebServerRequest *request, uint8_t *data, size_t len, size_t index, size_t total) {
            if (total > 0 && request->_tempObject == NULL) {
                request->_tempObject = malloc(total);
            }
            if (request->_tempObject != NULL) {
                memcpy((uint8_t*)(request->_tempObject) + index, data, len);
            }
        });

        handler = Web::server.on("/api/wifi/check", HTTP_GET, [] (AsyncWebServerRequest *request) {}, nullptr, [] (AsyncWebServerRequest* request, uint8_t* data, size_t len, size_t index, size_t total) {
            if (!Wifi::getCheck()->finished) {
                request->send(404, "", "");
                return;
            }

            DynamicJsonDocument result(1024);

            result["success"] = Wifi::getCheck()->succeed;
            result["ip"] = Wifi::getCheck()->ip;

            AsyncResponseStream *response = request->beginResponseStream("application/json");
            serializeJson(result, *response);
            request->send(response);
        });*/

        handler = Web::server.on("/api/setup", HTTP_POST, [] (AsyncWebServerRequest *request) {}, nullptr, [] (AsyncWebServerRequest* req, uint8_t* data, size_t len, size_t index, size_t total) {
            if(init) return;

            DynamicJsonDocument bodyJSON(384);
            deserializeJson(bodyJSON, data, len);

            if(!Config::setupConfig(bodyJSON)) {
                log_i("failed");
                bodyJSON.clear();
                req->send_P(401, "application/json; charset=UTF-8", R"==({"success": false})==");
                return;
            }

            bodyJSON.clear();
            req->send_P(200, "application/json; charset=UTF-8", R"==({"success": true})==");

            init = true;

            vTaskDelay(500 / portTICK_PERIOD_MS);
            //State::switchState(STATE_NORMAL); // TODO
            ESP.restart();
        });

        Web::start();
    }

    void stop() {
        Web::stop();

        Web::server.removeHandler(&wifi_scan_hander);
        //Web::server.removeHandler(&wifi_check_handler);
        Web::server.removeHandler(&handler);
        
        Wifi::stopScaning();
        Wifi::stopAP();

        vTaskDelete(task_led);

        StateNormal::start();
    }
}