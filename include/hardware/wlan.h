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
#if !defined(_WLAN_H)
#define _WLAN_H

#include <list>

#define INCLUDE_xTaskGetHandle                          1
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <WiFi.h>
#include <DNSServer.h>
#include "ESPmDNS.h"

#include "feature/config.h"

namespace Wifi {

    struct WifiEntry {
        String ssid;
        int32_t rssi;
        bool secure;

        WifiEntry(
            String ssid,
            int32_t rssi,
            bool secure) {
                this->ssid = ssid;
                this->rssi = rssi;
                this->secure = secure;
            }
    };

    struct WifiCheck {
        bool succeed;
        String ip;
    };

    void init();

    void startScaning();
    void stopScaning();
    void getWifis(JsonArray* array);

    WifiCheck check(const char * ssid, const char * password);

    void startAP();
    void stopAP();

    void connect();
    void disconnect();

    void startNormal();
    void stopNormal();

    bool isAP();
    bool isConnected();

}

#endif