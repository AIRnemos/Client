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

#if !defined(_UPDATE_H)
#define _UPDATE_H

#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <HTTPUpdate.h>

#include "hardware/firmware.h"
#include "hardware/wlan.h"
#include "version.h"

namespace OTAUpdate
{
    
    void init();
    void start();
    void stop();

} // namespace Update

#endif