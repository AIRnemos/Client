/*
    AIRnemos is a software for CO2 meter.
    Copyright (C) 2023 Quentin Schuster

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "main.h"

TaskHandle_t task_led;

void ledTask(void * parameter) {
  uint8_t brighness;

  for (;;)
  {
      brighness = beatsin8(10, 50, 255);
      FastLED.showColor(CHSV(160, 255, brighness));
      vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  log_i("Starting airnemos v%s...", VERSION);

  if (Config::initConfig()) {
    error(false);
  }

  Wifi::init();
  LED::init();
  Buzzer::init();

  xTaskCreatePinnedToCore(ledTask, "LED-Main", 2048, NULL, 5, &task_led, 0);

  if (Sensor::init()) {
    error(true);
  }

  Web::init();

  vTaskDelete(task_led);

  if(*Config::mustSetup())
    StateSetup::start();
  else
    StateNormal::start();

  log_i("Started airnemos core.");
  vTaskDelete(NULL);
}

void loop() {}

void error(bool ledInit) {
  if(ledInit) {
    vTaskDelete(task_led);
  } else {
    LED::init();
  }

  uint8_t brighness;
  while (true)
    {
      brighness = beatsin8(10, 50, 255);
      FastLED.showColor(CHSV(0, 255, brighness));
    }
}