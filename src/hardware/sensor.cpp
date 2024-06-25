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
#include "hardware/sensor.h"

namespace Sensor {
    SCD4x scd4x;

    uint16_t co2;
    float temperature;
    float humidity;

    bool init() {
        Wire.begin(SDA_PIN, SCL_PIN);
        
        scd4x.begin(Wire);

        char errorMessage[256];

        return !scd4x.begin();
    }

    bool read() {
        char errorMessage[256];
        bool error = !scd4x.readMeasurement();
        
        if (error) {
            return true;
        }

        co2 = scd4x.getCO2();
        temperature = scd4x.getTemperature();
        humidity = scd4x.getHumidity();

        return false;
    }

    bool calibrate() {
        char errorMessage[256];
        bool error = !scd4x.stopPeriodicMeasurement();
        
        if (error) {
            return true;
        }

        error = !scd4x.setAutomaticSelfCalibrationEnabled(false);
        
        if (error) {
            return true;
        }

        float frc;
        error = !scd4x.performForcedRecalibration(400, &frc);
        
        if (error) {
            return true;
        } else if(frc == 0xffff) {
            return true;
        }

        delay(1000);

        error = !scd4x.startPeriodicMeasurement();
        
        if (error) {
            return true;
        }

        return false;
    }
}
