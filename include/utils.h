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
#if !defined(UTILS)
#define UTILS

#include <Arduino.h>
#include <FastLED.h>


String toHex(int number);

String colorToString(CRGB color);

char* convertNumber(char* buffer, int value);

char* convertNumber(char* buffer, float value);

char* convertNumber(char* buffer, uint32_t value);

#endif // UTILS