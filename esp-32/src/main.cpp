#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>
#include "Logger/Logger.h"
#include "SettingsManager/SettingsManager.h"
#include "LedManager/LedManager.h"
#include "Utils/Utils.h"

#include "definitions.h"

#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h>
#else
  #include <SPIFFS.h>
#endif
#include "Controllers/ControllerSerial/ControllerSerial.h"

void setup()
{
  pinMode(2, OUTPUT);
  Serial.begin(460800);

  SPIFFS.begin();

  Logger::config();
  SettingsManager *settings = SettingsManager::getInstance();

  LedManager::setup();
  ControllerSerial::setup();

  settings->setup(); 
}

void loop()
{
  vTaskDelete(NULL);
}
