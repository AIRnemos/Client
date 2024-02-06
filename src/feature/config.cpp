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
#include "feature/config.h"

namespace Config
{
    bool needSetup = false;

    String filesystemVersion = "none";

    // Device variables
    String defaultName = "AIRnemos";
    String serialNumber = "none";
    uint8_t ledsNum = 16;


    // Config variables
    String name = "";
    String password = "";

    uint16_t thresholdGood = 1000;
    uint16_t thresholdBad = 2000;

    CRGB colorGood = CRGB::Green;
    CRGB colorBad = CRGB::Red;

    bool buzzer = true;

    byte wifiMode = WIFI_MODE_ACCESS_POINT;
    String wifiSsid;
    String wifiPassword;
    int16_t wifiRetries;

    byte wifiFallback = WIFI_MODE_NONE;
    String wifiFallbackSsid;
    String wifiFallbackPassword;
    int16_t wifiFallbackRetries;

    void setSetup() {
        needSetup = true;
    }


    void readDeviceValues() {
        File file = LittleFS.open("/device.json", "r");

        if(!file) {
            log_w("Can't open \"device.json\". Use default vaules.");
            return;
        }

        if(file.isDirectory()) {
            log_w("\"device.json\" is a folder. Use default vaules.");
            return;
        }

        StaticJsonDocument<128> doc;
        DeserializationError error = deserializeJson(doc, file);

        if (error) {
            log_w("Can't parse \"device.json\". (%s) Use default vaules.", error.c_str());
            return;
        }

        defaultName = (String) doc["name"].as<String>();
        serialNumber = (String) doc["serial"].as<String>();
        ledsNum = doc["leds"];
    }

    bool readFilesytemVersion() {
        if(!LittleFS.exists("/VERSION")) {
            return true;
        }

        File file = LittleFS.open("/VERSION", "r");

        if(!file) {
            log_w("Can't open \"VERSION\". Start setup.");
            return true;
        }

        if(file.isDirectory()) {
            LittleFS.remove("/VERSION");
            log_w("\"VERSION\" is a folder. Start setup.");
            return true;
        }

        filesystemVersion = file.readString();
        return false;
    }

    bool initConfig() {
        log_i("Initialising Filesystem...");
        if(!LittleFS.begin()) {
            log_e("Can't initialised Filesystem.");
            return true;
        }
        log_i("Initialised Filesystem.");

        if(!LittleFS.exists("/device.json")) {
            log_w("\"device.json\" not found. Use default vaules.");
        } else readDeviceValues();

        if(readFilesytemVersion()) {
            setSetup();
            return false;
        }

        if(!LittleFS.exists("/config.json")) {
            log_w("\"config.json\" not found. Start setup.");
            setSetup();
            return false;
        }

        File file = LittleFS.open("/config.json", "r");

        if(!file) {
            log_w("Can't open \"config.json\". Start setup.");
            setSetup();
            return false;
        }

        if(file.isDirectory()) {
            LittleFS.remove("/config.json");
            log_w("\"config.json\" is a folder. Start setup.");
            setSetup();
            return false;
        }

        StaticJsonDocument<512> doc;
        DeserializationError error = deserializeJson(doc, file);

        if (error) {
            log_w("Can't parse \"config.json\". (%s)", error.c_str());
            return true;
        }

        JsonObject obj = doc.as<JsonObject>();

        set(&obj);

        return false;
    }

    bool setupConfig(DynamicJsonDocument json) {
        if (!json.containsKey("name")) return false;
        if (!json.containsKey("password")) return false;

        if (!json.containsKey("buzzer")) return false;
        
        if (!json.containsKey("wifi")) return false;
        if (!json["wifi"].containsKey("mode")) return false;
        
        if (json["wifi"]["mode"] > 0) {
            if (!json["wifi"].containsKey("ssid")) return false;
            if (!json["wifi"].containsKey("password")) return false;
            
            if(json["wifi"]["mode"] == 2 && !json["wifi"].containsKey("retires")) return false;
        }
        
        if (!json["wifi"].containsKey("fallback")) return false;
        if (!json["wifi"]["fallback"].containsKey("mode")) return false;
       
        if (json["wifi"]["fallback"]["mode"] > 0) {
            if (!json["wifi"]["fallback"].containsKey("ssid")) return false;
            if (!json["wifi"]["fallback"].containsKey("password")) return false;
        }

        JsonObject object = json.as<JsonObject>();
        set(&object);

        File versionFile = LittleFS.open("/VERSION", "w");
        versionFile.print("1");
        versionFile.close();
        save();

        needSetup = false;
        return true;
    }

    bool* mustSetup() {
        return &needSetup;
    }

    void save() {
        StaticJsonDocument<512> doc = StaticJsonDocument<512>();
        get(&doc);
        File config = LittleFS.open("/config.json", "w");
        serializeJson(doc, config);
        config.close();
        doc.garbageCollect();
    }    

    void get(StaticJsonDocument<512>* doc) {
        (*doc)["name"] = name; 
        (*doc)["password"] = password; 

        JsonObject color = (*doc).createNestedObject("color");
        color["good"] = colorToString(colorGood);
        color["bad"] = colorToString(colorBad);

        JsonObject threshold = (*doc).createNestedObject("threshold");
        threshold["good"] = thresholdGood;
        threshold["bad"] = thresholdBad;

        (*doc)["buzzer"] = buzzer;

        JsonObject wifi = (*doc).createNestedObject("wifi");
        wifi["mode"] = wifiMode;
        wifi["ssid"] = wifiSsid;
        wifi["password"] = wifiPassword;
        wifi["retires"] = wifiRetries;

        JsonObject wifiFallbackJ = wifi.createNestedObject("fallback");
        wifiFallbackJ["mode"] = wifiFallback;
        wifiFallbackJ["ssid"] = wifiFallbackSsid;
        wifiFallbackJ["password"] = wifiFallbackPassword;
        wifiFallbackJ["retires"] = wifiFallbackRetries;
    }

    CRGB parseColor(char* color) {
        return strtol(color, NULL, 16);
    }

    void set(JsonObject* doc) {
        if (doc->containsKey("name"))
            name = (*doc)["name"].as<String>(); 
        if (doc->containsKey("password"))
            password = (*doc)["password"].as<String>(); 

        if (doc->containsKey("color")) {
            JsonObject color = (*doc)["color"];

            if(color.containsKey("good"))
                colorGood = parseColor((char*) color["good"].as<String>().c_str());
            if(color.containsKey("bad"))
                colorBad = parseColor((char*) color["bad"].as<String>().c_str());
        }
        
        if (doc->containsKey("threshold")) {
            JsonObject threshold = (*doc)["threshold"];

            if(threshold.containsKey("good"))
                thresholdGood = threshold["good"];
            if(threshold.containsKey("bad"))
                thresholdBad = threshold["bad"];
        }

        if (doc->containsKey("buzzer"))
            buzzer = (*doc)["buzzer"];

        if (doc->containsKey("wifi")) {
            JsonObject wifi = (*doc)["wifi"];
            if(wifi.containsKey("mode"))
                wifiMode = wifi["mode"];
            if(wifi.containsKey("ssid"))
                wifiSsid = wifi["ssid"].as<String>();
            if(wifi.containsKey("password"))
                wifiPassword = wifi["password"].as<String>();
            if(wifi.containsKey("retires"))
                wifiRetries = wifi["retires"];

            if(wifi.containsKey("fallback")) {
                JsonObject fallback = wifi["fallback"];
                if(fallback.containsKey("mode"))
                    wifiFallback = fallback["mode"];
                if(fallback.containsKey("ssid"))
                    wifiFallbackSsid = fallback["ssid"].as<String>();
                if(fallback.containsKey("password"))
                    wifiFallbackPassword = fallback["password"].as<String>();
                if(fallback.containsKey("retires"))
                    wifiFallbackRetries = fallback["retires"];
            }
        }
    }
    
}
