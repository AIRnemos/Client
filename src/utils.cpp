#include "utils.h"

String toHex(int number) {
    char buffer[10];
    sprintf(buffer, "%02X", number);
    return buffer;
}

String colorToString(CRGB color) {
    String colorString;
    char buffer[2];

    sprintf(buffer, "%02X", color.r);
    colorString += buffer;
    sprintf(buffer, "%02X", color.g);
    colorString += buffer;
    sprintf(buffer, "%02X", color.b);
    colorString += buffer;

    return colorString;
}

char* convertNumber(char* buffer, int value) {
    itoa(value, buffer, 10);
    return buffer;
}

char* convertNumber(char* buffer, float value) {
    dtostrf(value, 6, 2, buffer);
    return buffer;
}

char* convertNumber(char* buffer, uint32_t value) {
    dtostrf(value, 6, 2, buffer);
    return buffer;
}