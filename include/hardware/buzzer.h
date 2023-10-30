#if !defined(_BUZZER_H)
#define _BUZZER_H

#include <Arduino.h>

#include "firmware.h"
#include "feature/config.h"

namespace Buzzer {
    void init();

    void high();
    void low();
}

#endif