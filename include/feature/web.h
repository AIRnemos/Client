#if !defined(_WEB_H)
#define _WEB_H

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>


#include "feature/config.h"
#include "hardware/wlan.h"

namespace Web {
    extern AsyncWebServer server;

    void init();
    void start();
    void stop();
}

#endif