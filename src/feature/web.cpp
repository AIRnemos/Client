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

    extern const uint8_t logo_data[] asm("_binary_web_dist_assets_logo_svg_start");

    //extern const uint8_t api_css_data[] asm("_binary_web_dist_assets_api_css_start");
    extern const uint8_t settings_css_data[] asm("_binary_web_dist_assets_settings_css_start");
    extern const uint8_t index_css_data[] asm("_binary_web_dist_assets_index_css_start");

    extern const uint8_t index2_js_data[] asm("_binary_web_dist_assets_index2_js_start");
    extern const uint8_t de_js_data[] asm("_binary_web_dist_assets_de_js_start");
    //extern const uint8_t api_js_data[] asm("_binary_web_dist_assets_api_js_start");
    extern const uint8_t en_js_data[] asm("_binary_web_dist_assets_en_js_start");
    //extern const uint8_t dashboard_js_data[] asm("_binary_web_dist_assets_dashboard_js_start");
    extern const uint8_t settings_js_data[] asm("_binary_web_dist_assets_settings_js_start");
    extern const uint8_t index_js_data[] asm("_binary_web_dist_assets_index_js_start");

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

        server.on("/assets/logo.svg", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "image/svg+xml", (char*) logo_data);
        });

        /* server.on("/assets/api.css", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "text/css", (char*) api_css_data);
        }); */
        server.on("/assets/settings.css", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "text/css", (char*) settings_css_data);
        });
        server.on("/assets/index.css", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "text/css", (char*) index_css_data);
        });

        server.on("/assets/index2.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) index2_js_data);
        });
        server.on("/assets/de.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) de_js_data);
        });
       /*  server.on("/assets/api.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) api_js_data);
        }); */
        server.on("/assets/en.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) en_js_data);
        });
        /* server.on("/assets/dashboard.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) dashboard_js_data);
        }); */
        server.on("/assets/settings.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) settings_js_data);
        });
        server.on("/assets/index.js", [] (AsyncWebServerRequest *request) {
            request->send_P(200, "application/javascript", (char*) index_js_data);
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
    }
}
