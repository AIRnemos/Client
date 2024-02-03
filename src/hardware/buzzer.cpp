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
#include "hardware/buzzer.h"

namespace Buzzer {
    void init() {
        pinMode(BUZZER_PIN, OUTPUT);
    }

    void high() {
        tone(BUZZER_PIN, 440, BUZZER_DURATION * 0.9);
        delay(BUZZER_DURATION);
        tone(BUZZER_PIN, 554, BUZZER_DURATION * 0.9);
        delay(BUZZER_DURATION);
        tone(BUZZER_PIN, 659, BUZZER_DURATION * 0.9);
    }
    void low() {
        tone(BUZZER_PIN, 523, BUZZER_DURATION * 0.9);
        delay(BUZZER_DURATION);
        tone(BUZZER_PIN, 659, BUZZER_DURATION * 0.9);
        delay(BUZZER_DURATION);
        tone(BUZZER_PIN, 784, BUZZER_DURATION * 0.9);
    }
}