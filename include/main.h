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
#if !defined(_MAIN_H)
#define _MAIN_H

#include <Arduino.h>

#include "feature/config.h"
#include "hardware/wlan.h"
#include "feature/web.h"
#include "state/setup.h"
#include "state/normal.h"
#include "hardware/led.h"
#include "hardware/sensor.h"
#include "hardware/buzzer.h"
#include "version.h"

void error(bool ledInit);

#endif