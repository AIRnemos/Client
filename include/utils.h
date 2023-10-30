#if !defined(UTILS)
#define UTILS

#include <Arduino.h>
#include <FastLED.h>


String toHex(int number);

String colorToString(CRGB color);

char* convertNumber(char* buffer, int value);

char* convertNumber(char* buffer, float value);

char* convertNumber(char* buffer, uint32_t value);

#endif // UTILS