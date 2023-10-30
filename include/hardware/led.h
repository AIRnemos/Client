#if !defined(_LED_H)
#define _LED_H

#include <FastLED.h>

#include "firmware.h"
#include "feature/config.h"

// TODO: status LED
namespace LED {
    extern CRGB leds[LEDS];

    void init();
}

#endif