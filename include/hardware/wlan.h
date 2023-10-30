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