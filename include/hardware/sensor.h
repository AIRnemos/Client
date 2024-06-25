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
#if !defined(_SENSOR_H)
#define _SENSOR_H

#include <SparkFun_SCD4x_Arduino_Library.h>
#include <Wire.h>

#include "firmware.h"

namespace Sensor {
    
    extern uint16_t co2;
    extern float temperature;
    extern float humidity;

    bool init();
    bool read();
    bool calibrate();
}

#endif