#include "hardware/sensor.h"

namespace Sensor {
    SensirionI2CScd4x scd4x;

    uint16_t co2;
    float temperature;
    float humidity;

    bool init() {
        Wire.begin(SDA_PIN, SCL_PIN);
        
        scd4x.begin(Wire);

        char errorMessage[256];

        scd4x.stopPeriodicMeasurement();
        uint16_t error = scd4x.startPeriodicMeasurement();

        if (error) {
            errorToString(error, errorMessage, 256);
            log_e("%s", errorMessage);
            return true;
        } else {
            return false;
        }
    }

    bool read() {
        char errorMessage[256];
        uint16_t error = scd4x.readMeasurement(co2, temperature, humidity);
        
        if (error) {
            errorToString(error, errorMessage, 256);
            log_e("%s", errorMessage);
            return true;
        } else if (co2 == 0) {
            Serial.println("Sensor\t Invalid sample detected, skipping.");
            return true;
        } else {
            return false;
        }
    }

    bool calibrate() {
        char errorMessage[256];
        uint16_t error = scd4x.stopPeriodicMeasurement();
        
        if (error) {
            errorToString(error, errorMessage, 256);
            log_e("%s", errorMessage);
            return true;
        }

        error = scd4x.setAutomaticSelfCalibration(0);
        
        if (error) {
            errorToString(error, errorMessage, 256);
            log_e("%s", errorMessage);
            return true;
        }

        uint16_t frc;
        error = scd4x.performForcedRecalibration(400, frc);
        
        if (error) {
            errorToString(error, errorMessage, 256);
            log_e("%s", errorMessage);
            return true;
        }else if(frc == 0xffff) {
            return true;
        }

        delay(1000);

        error = scd4x.startPeriodicMeasurement();
        
        if (error) {
            errorToString(error, errorMessage, 256);
            log_e("%s", errorMessage);
            return true;
        }

        return false;
    }
}
