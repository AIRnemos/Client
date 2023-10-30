#include "hardware/buzzer.h"

namespace Buzzer {
    void init() {
        pinMode(BUZZER_PIN, OUTPUT);
    }

    void high() {
        tone(BUZZER_PIN, 440, BUZZER_DURATION * 0.9);
        delay(BUZZER_DURATION);
        tone(BUZZER_PIN, 554, BUZZER_DURATION * 0.9);
        delay(BUZZER_DURATION);
        tone(BUZZER_PIN, 659, BUZZER_DURATION * 0.9);
    }
    void low() {
        tone(BUZZER_PIN, 523, BUZZER_DURATION * 0.9);
        delay(BUZZER_DURATION);
        tone(BUZZER_PIN, 659, BUZZER_DURATION * 0.9);
        delay(BUZZER_DURATION);
        tone(BUZZER_PIN, 784, BUZZER_DURATION * 0.9);
    }
}