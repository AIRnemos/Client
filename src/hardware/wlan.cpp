#include "hardware/wlan.h"

#define WIFI_EVENT_GOT_IP_BIT (1UL << 0UL)

#define WIFI_EVENT_CONNECTED_BIT (1UL << 1UL)
#define WIFI_EVENT_DISCONNECTED_BIT (1UL << 2UL)

#define WIFI_EVENT_STOP_BIT (1UL << 2UL)

#define WIFI_SCAN_START 1
#define WIFI_SCAN_STOP 2
#define WIFI_SCAN_DONE 3


namespace Wifi {

    const IPAddress apIP(192, 168, 1, 1);
    const IPAddress netMask(255, 255, 255, 0);


    DNSServer server;

    std::list<WifiEntry> entries;

    // Tasks
    EventGroupHandle_t eventGroup;

    TaskHandle_t task_scan;
    TaskHandle_t task_dns;
    TaskHandle_t task_wifi;

    void scanTask(void * parameter) { 
        uint32_t thread_notification;
        bool stop = false;

        for(;;) {
            thread_notification = 0;
            xTaskNotifyWait(ULONG_MAX, ULONG_MAX, &thread_notification, portMAX_DELAY);

            switch (thread_notification)
            {
            case WIFI_SCAN_START:
                WiFi.disconnect();
            case WIFI_SCAN_DONE: 
                if(stop) {
                    stop = false;
                    break;
                }

                vTaskDelay(5000 / portTICK_PERIOD_MS);
                WiFi.scanNetworks(true);
                break;
            case WIFI_SCAN_STOP:
                stop = true;
                break;
            }
        }
    }

    void dnsTask(void * parameter) {
        server.start(53, "*", apIP);
        log_i("Started DNS-Server!");

        for (;;)
        {
           server.processNextRequest();
           vTaskDelay(500 / portTICK_PERIOD_MS);
        }
    }

    void wifiTask(void * parameter) {
        
        if(Config::wifiMode == WIFI_MODE_ACCESS_POINT) {
            startAP();
        } else if(Config::wifiMode == WIFI_MODE_WIFI) {
            connect();   
        }

        for(;;) {
            EventBits_t data = xEventGroupWaitBits(eventGroup, WIFI_EVENT_DISCONNECTED_BIT | WIFI_EVENT_STOP_BIT, pdTRUE, pdFALSE, 10000 / portTICK_PERIOD_MS);

            // TODO: fallback and tries
            if((data & WIFI_EVENT_DISCONNECTED_BIT) != 0) {
                connect();
            } else if((data & WIFI_EVENT_STOP_BIT) != 0) {
                if(isAP())
                    stopAP();
                else if(isConnected())
                    disconnect();
                break;
            }
        }
    }

    // Callbacks

    void scanDone(WiFiEvent_t event, WiFiEventInfo_t info){
        xTaskNotify(task_scan, WIFI_SCAN_DONE, eSetValueWithoutOverwrite);

        int n = WiFi.scanComplete();
        
        if(n == -2) return;

        entries.clear();

        for(int i = 0; i < n; i++) {
            entries.push_back(WifiEntry(WiFi.SSID(i), WiFi.RSSI(i), WiFi.encryptionType(i) != WIFI_AUTH_OPEN));
        }
        
        WiFi.scanDelete();
    }

    void wifiConnected(WiFiEvent_t event, WiFiEventInfo_t info) {
        xEventGroupSetBits(eventGroup, WIFI_EVENT_CONNECTED_BIT);
    }
    void wifiDisconnected(WiFiEvent_t event, WiFiEventInfo_t info) {
        xEventGroupSetBits(eventGroup, WIFI_EVENT_DISCONNECTED_BIT);
    }
    void wifiGotIp(WiFiEvent_t event, WiFiEventInfo_t info) {
        xEventGroupSetBits(eventGroup, WIFI_EVENT_GOT_IP_BIT);
    }



    void init() {
        eventGroup = xEventGroupCreate();

        WiFi.onEvent(scanDone, ARDUINO_EVENT_WIFI_SCAN_DONE);
        WiFi.onEvent(wifiConnected, ARDUINO_EVENT_WIFI_STA_CONNECTED);
        WiFi.onEvent(wifiDisconnected, ARDUINO_EVENT_WIFI_STA_DISCONNECTED);
        WiFi.onEvent(wifiGotIp, ARDUINO_EVENT_WIFI_STA_GOT_IP);

        WiFi.mode(WIFI_MODE_APSTA);

        xTaskCreate(scanTask, "Wifi-Scan", 4096, NULL, 5, &task_scan);
    }


    void startScaning() {
        xTaskNotify(task_scan, WIFI_SCAN_START, eSetValueWithoutOverwrite);
    }

    void stopScaning() {
        xTaskNotify(task_scan, WIFI_SCAN_STOP, eSetValueWithOverwrite);
    }

    void getWifis(JsonArray* array) {
        for (WifiEntry entry : entries) {
            JsonObject data = array->createNestedObject();

            data["ssid"] = entry.ssid;
            data["rssi"] = entry.rssi;
            data["secure"] = entry.secure;
        } 
    }


    WifiCheck check(const char * ssid, const char * password) {
        WifiCheck returnValue;
        wl_status_t status =  WiFi.begin(ssid, password);

        if(status == WL_CONNECT_FAILED) {
            returnValue.succeed = false;
            returnValue.ip = "";

            WiFi.disconnect();

            return returnValue;
        }

        // TODO: catch watchdog
        EventBits_t data = xEventGroupWaitBits(eventGroup, WIFI_EVENT_CONNECTED_BIT | WIFI_EVENT_DISCONNECTED_BIT, pdTRUE, pdFALSE, 10000 / portTICK_PERIOD_MS);

        if((data & WIFI_EVENT_CONNECTED_BIT) == 0 && (data & WIFI_EVENT_DISCONNECTED_BIT) != 0) {
            returnValue.succeed = false;
            returnValue.ip = "";

            WiFi.disconnect();

            return returnValue;
        }

        data = xEventGroupWaitBits(eventGroup, WIFI_EVENT_GOT_IP_BIT, pdTRUE, pdFALSE, 5000 / portTICK_PERIOD_MS);

        if((data & WIFI_EVENT_GOT_IP_BIT) == 0 ) {
            returnValue.succeed = false;
            returnValue.ip = "";

            WiFi.disconnect();

            return returnValue;
        } // TODO: better error handling

        returnValue.succeed = true;
        returnValue.ip = WiFi.localIP().toString();

        WiFi.disconnect();

        return returnValue;
    }


    void startAP() {
        WiFi.softAPConfig(apIP, apIP, netMask);
        WiFi.softAP(Config::wifiAPSsid.c_str(), Config::wifiAPPassword.c_str());
        xTaskCreate(dnsTask, "Wifi-DNS", 4096, NULL, 5, &task_dns);

        // TODO: captive portal not working
    }

    void stopAP() {
        vTaskDelete(task_dns);
        server.stop();
    }

    void connect() {
        WiFi.begin(Config::wifiSsid.c_str(), Config::wifiPassword.c_str());
    }

    void disconnect() {
        WiFi.disconnect();
    }

    void startNormal() {
        xTaskCreate(wifiTask, "Wifi", 4096, NULL, 5, &task_wifi);
    }
    
    void stopNormal() {
        xEventGroupSetBits(eventGroup, WIFI_EVENT_STOP_BIT);
    }


    bool isAP() {
        return WiFi.softAPIP() != IPAddress();
    }

    bool isConnected() {
        return WiFi.isConnected();
    }
}