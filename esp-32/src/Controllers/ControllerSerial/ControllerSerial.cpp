#pragma once
#include <ArduinoJson.h>
#include "ControllerSerial.h"
#include "LedManager/LedManager.h"
#include "Logger/Logger.h"
#include "Types/Color/Color.h"
#include "Types/Gradient.h"
#include "Utils/Utils.h"
#include "SettingsManager/SettingsManager.h"

String a = "a";

void ControllerSerial::setup()
{ 
    xTaskCreate([](void *params){
      while (true){
        if (Serial.available()){
          digitalWrite(2, HIGH);
          String data = Serial.readStringUntil('\n');
          Serial.flush();
          handleSerialMessage(data);
          SettingsManager::getInstance()->setLastMessage(data);
          }
        digitalWrite(2, LOW);
      }
    },
    "serial", 5000, NULL, 1, NULL);
}

void ControllerSerial::handleSerialMessage(String data)
{
  DynamicJsonDocument doc(3072); // Worst case with custom effect with 20 elements

  DeserializationError error = deserializeJson(doc, data);

  if (error)
    return Logger::error("deserializeJson() failed: " + String(error.c_str()));


  const char *event = doc["event"];

  if (String(event) == "color")
  {
    JsonObject jsonData = doc["data"];
    LedManager::setColor(Color(jsonData));
  }
  else if (String(event) == "gradient")
  {
    JsonArray jsonArray = doc["data"];
    Gradient *gradient = new Gradient(jsonArray);
    // doc.clear();
    LedManager::setGradient(gradient);
  }
  // else if (String(event)=="effect") LedManager::setColor(Color(jsonData));
}