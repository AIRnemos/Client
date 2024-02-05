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
#include "state/manager.h"

namespace State
{
    TaskHandle_t loopTask;
    byte current;

    void start(byte mode) {
        switch (mode)
        {
            case STATE_SETUP:
                StateSetup::start();
                break;
            case STATE_NORMAL:
                StateNormal::start();
                break;
        }
    }

    void stop(byte mode) {
        switch (mode)
        {
            case STATE_SETUP:
                StateSetup::stop();
                break;
            case STATE_NORMAL:
                StateNormal::stop();
                break;
        }
    }

    void loop(void * parameter) {
        start(current);

        uint32_t newMode;
        for (;;)
        {
            xTaskNotifyWait(0x00, ULONG_MAX, &newMode, portMAX_DELAY);

            if(newMode > 1) continue;
            if(newMode == current) continue;

            stop(current);
            start(newMode);

            current = newMode;
        }
        
    }


    void init(byte mode) {
        current = mode;
        xTaskCreate(loop, "StateManager", 4096, NULL, 5, &loopTask);  
    } 

    void switchState(byte mode) {
        xTaskNotify(loopTask, mode, eSetValueWithOverwrite);
    }
} // namespace State
