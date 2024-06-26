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
#include "feature/web.h"

namespace Web {

    AsyncWebServer server(80);

    //extern const uint8_t logo_data[] asm("_binary_web_dist_assets_logo_png_start");
    //extern const uint8_t logo_data_end[] asm("_binary_web_dist_assets_logo_png_end");
    /*server.on("/assets/logo.png", [] (AsyncWebServerRequest *request) {
        AsyncWebServerResponse *response = request->beginResponse_P(200, "image/png", (uint8_t *) logo_data, logo_data_end - logo_data);
        request->send(response);
    });*/

    extern const uint8_t index_html_data[] asm("_binary_web_dist_index_html_start");
    
    extern const uint8_t index_css_data[] asm("_binary_web_dist_assets_index_css_start");
    extern const uint8_t card_js_data[] asm("_binary_web_dist_assets_card_js_start");
    extern const uint8_t settings_lazy_js_data[] asm("_binary_web_dist_assets_settings_lazy_js_start");
    extern const uint8_t index_js_data[] asm("_binary_web_dist_assets_index_js_start");
    extern const uint8_t index_lazy_js_data[] asm("_binary_web_dist_assets_index_lazy_js_start");
   
    void init() {
        server.on("/", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "text/html", (char*) index_html_data, [] (const String& var) {
                if(var == "name") {
                    return  *Config::mustSetup() ? Config::defaultName : Config::name;
                } else if(var == "setup") {
                    return *Config::mustSetup() ? String("true") : String("false");
                } else if(var == "ap") {
                    return Wifi::isAP() ? String("true") : String("false");
                }
                String data = "%" + var + "%";
                return data;
            });
        });

        server.on("/assets/index.css", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "text/css", (char*) index_css_data);
        });
        server.on("/assets/card.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) card_js_data);
        });
        server.on("/assets/settings.lazy.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) settings_lazy_js_data);
        });
        server.on("/assets/index.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) index_js_data);
        });
        server.on("/assets/index.lazy.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) index_lazy_js_data);
        });
        

        server.on("/hotspot-detect.html", [](AsyncWebServerRequest *request) { // iphone doesn't load normal
            request->send(200, "text/html", "<html><head><meta http-equiv=\"refresh\" content=\"0; url=http://" + WiFi.softAPIP().toString() + "/\" /></head></html>");
        });
        server.onNotFound([] (AsyncWebServerRequest *request) {
            if(ON_AP_FILTER(request))
                request->redirect("http://" + WiFi.softAPIP().toString() + "/");
            else
                request->redirect("http://" + WiFi.localIP().toString() + "/");
        });
    }

    void start() {
        server.begin();
    }
    void stop() {
        server.end();
        server.reset();
    }
}
