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