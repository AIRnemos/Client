#if !defined(_SENSOR_H)
#define _SENSOR_H

#include <SensirionI2CScd4x.h>
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