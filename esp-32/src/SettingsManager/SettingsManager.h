#pragma once
#include <Arduino.h>
#include "Types/Color/Color.h"

#define CONFIG_FILENAME "/cfg"

class SettingsManager {
  private:
    void getSettingsFromFile();
    void saveSettingsToFile();
  public:
    String lastMessage;
    void setLastMessage(String message);
    void setup();
    static SettingsManager* getInstance();
    void debug();
};