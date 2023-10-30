#if !defined(_CONFIG_H)
#define _CONFIG_H

#include <Arduino.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include "hardware/led.h"
#include "utils.h"


#define WIFI_MODE_ACCESS_POINT 1
#define WIFI_MODE_WIFI 2
#define WIFI_MODE_NONE 0


namespace Config {

    extern String defaultName;
    extern String serialNumber;
    extern uint8_t ledsNum;


    extern String name;
    extern String password;

    extern CRGB colorGood;
    extern CRGB colorBad;

    extern bool buzzer;

    extern uint16_t thresholdGood;
    extern uint16_t thresholdBad;

    extern byte wifiMode;
    extern byte wifiFallback;
    extern String wifiSsid;
    extern String wifiPassword;
    extern int16_t wifiRetries;
    extern String wifiAPSsid;
    extern String wifiAPPassword;

    bool initConfig();
    bool setupConfig(DynamicJsonDocument json);

    bool* mustSetup();

    void save();
    void get(StaticJsonDocument<512>* doc);
    void set(JsonObject* doc);
}

#endif