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
}

void loop() {
  vTaskDelay(1000 / portTICK_PERIOD_MS);
  if(digitalRead(8) == LOW) {
    LittleFS.remove("/config.json");
    LittleFS.remove("/VERSION");
    ESP.restart();
  }
}

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