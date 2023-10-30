#if !defined(_NORMAL_H)
#define _NORMAL_H

#include <ArduinoJson.h>

#include "feature/config.h"
#include "hardware/wlan.h"
#include "feature/web.h"
#include "utils.h"
#include "hardware/sensor.h"
#include "hardware/led.h"
#include "hardware/buzzer.h"
#include "hardware/rtc.h"

#define BUFFER_SIZE 60

namespace StateNormal {
    void start();
    void stop();
}

#endif