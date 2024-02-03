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