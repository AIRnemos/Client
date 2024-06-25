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
#include "utils.h"

String toHex(int number) {
    char buffer[10];
    sprintf(buffer, "%02X", number);
    return buffer;
}

String colorToString(CRGB color) {
    String colorString;
    char buffer[2];

    sprintf(buffer, "%02X", color.r);
    colorString += buffer;
    sprintf(buffer, "%02X", color.g);
    colorString += buffer;
    sprintf(buffer, "%02X", color.b);
    colorString += buffer;

    return colorString;
}

char* convertNumber(char* buffer, int value) {
    itoa(value, buffer, 10);
    return buffer;
}

char* convertNumber(char* buffer, float value) {
    dtostrf(value, 6, 2, buffer);
    return buffer;
}

char* convertNumber(char* buffer, uint32_t value) {
    dtostrf(value, 6, 2, buffer);
    return buffer;
}