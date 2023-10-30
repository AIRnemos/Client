#include "hardware/led.h"

namespace LED {
    CRGB leds[40];

    void init() {
        FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LEDS);
        FastLED.setBrightness(255);
    }
}
