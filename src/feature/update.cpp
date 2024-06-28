/*
    AIRnemos is a software for CO2 meter.
    Copyright (C) 2024 Quentin Schuster

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

#include "feature/update.h"

namespace OTAUpdate {

    WiFiClientSecure wifiClient;
    int16_t firmwareVersion[3];
    TaskHandle_t task_handle;

    extern const uint8_t rootca_crt_bundle_start[] asm("_binary_cert_bin_start");

    bool extractVersion(char* versionString, int16_t *versionParts);
    bool isHigher(int16_t *one, int16_t *two);

    bool check() {
        while(!Wifi::isConnected()) vTaskDelay(500 / portTICK_RATE_MS);

        HTTPClient http;
        http.useHTTP10(true);
        http.begin(wifiClient, "https://api.github.com/repos/" + ((String) GITHUB_REPO) + "/releases");

        int code = http.GET();
        log_i("Code: %d", code);

        if (code != 200) {
            http.end();
            wifiClient.stop();
            return false;
        }

        StaticJsonDocument<256> filter;
        filter[0]["tag_name"] = true;
        filter[0]["prerelease"] = true;
        filter[0]["draft"] = true;
        filter[0]["assets"][0]["name"] = true;
        filter[0]["assets"][0]["browser_download_url"] = true;

        DynamicJsonDocument json(2048*4);
        deserializeJson(json, http.getStream(), DeserializationOption::Filter(filter), DeserializationOption::NestingLimit(5));

        vPortYield();

        int16_t highestVersionParts[3] = {-1, -1, -1};
        JsonObject highest;

        for (JsonObject release : json.as<JsonArray>()) {
            if (release["draft"].as<bool>()) continue;
            if (release["prerelease"].as<bool>()) continue;

            int16_t versionParts[3];
            char* version = strdup(release["tag_name"].as<String>().substring(1).c_str());

            bool success = extractVersion(version, versionParts);

            free(version);            

            if(!success) continue;

            if(isHigher(versionParts, highestVersionParts)) {
                highestVersionParts[0] = versionParts[0];
                highestVersionParts[1] = versionParts[1];
                highestVersionParts[2] = versionParts[2];

                highest = release;
            }
            
            vPortYield();
        }

        if (isHigher(highestVersionParts, firmwareVersion)) { 
            log_i("New Version (v%d.%d.%d) found! Updating...", highestVersionParts[0], highestVersionParts[1], highestVersionParts[2]);

            for (JsonObject asset : highest["assets"].as<JsonArray>()) {
                log_i("%s == %s", asset["name"].as<String>().c_str(), GITHUB_ASSET);
                if (strcmp(asset["name"].as<String>().c_str(), GITHUB_ASSET) != 0) continue;

                http.end();

                http.begin(asset["browser_download_url"].as<String>().c_str());
                httpUpdate.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
                auto result = httpUpdate.update(http);

                if (result == HTTP_UPDATE_OK) {
                    ESP.restart();
                }

                return false;
            }

            log_e("Can't find asset: %s", GITHUB_ASSET);
            http.end();
            return false;
        }

        http.end();
        json.shrinkToFit();
        json.garbageCollect();

        return true;   
    }

    void task(void * param) {
        vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
        while(true) {
            check();
            vTaskDelay(60 * 60 * 1000 / portTICK_PERIOD_MS);
        }
    }

    void init() {
        char* version = strdup(VERSION);
        extractVersion(version, firmwareVersion);
        free(version);

        wifiClient.setCACertBundle(rootca_crt_bundle_start);
    }

    void start() {
        if (task_handle != NULL) return;

        xTaskCreate(task, "Update-Task", 16348, NULL, 5, &task_handle);
    }

    void stop() {
        if (task_handle == NULL) return;

        vTaskDelete(task_handle);
        task_handle = NULL;
    }

    bool extractVersion(char* versionString, int16_t *versionParts) {
        char* part = strtok(versionString, ".");
        versionParts[0] = -1;
        versionParts[1] = -1;
        versionParts[2] = -1;

        int8_t index = 0;

        while (part != NULL)
        {
            if (strcmp(part, "0") == 0) {
                versionParts[index] = 0;
            } else {
                versionParts[index] = (short) strtol(part, (char **)NULL, 10);

                if (versionParts[index] == 0) return false;
            }

            index++;

            if (index == 3) {
                part == NULL;
            }

            part = strtok(NULL, ".");
        }

        return index == 3;
    }

    bool isHigher(int16_t *versionPartsOne, int16_t *versionPartsTwo) {
        for (size_t i = 0; i < 3; i++)
        {
            if (versionPartsOne[i] <= versionPartsTwo[i]) continue;

            return true;
        }

        return false;
    }

}