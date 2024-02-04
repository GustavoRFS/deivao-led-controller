#include <ArduinoJson.h>

#include "SettingsManager.h"
#include "Logger/Logger.h"

#include "definitions.h"

#include <FS.h>
#ifdef USE_LITTLEFS
  #define SPIFFS LITTLEFS
  #include <LITTLEFS.h> 
#else
  #include <SPIFFS.h>
#endif 
#include <Controllers/ControllerSerial/ControllerSerial.h>

SettingsManager* settingsManagerInstance = nullptr;

void SettingsManager::setup(){
  getSettingsFromFile();

  SettingsManager* settings = SettingsManager::getInstance();

  ControllerSerial::handleSerialMessage(settings->lastMessage); 
}

void SettingsManager::getSettingsFromFile(){
  if (!SPIFFS.exists(CONFIG_FILENAME)) return;
  
  String configJson = SPIFFS.open(CONFIG_FILENAME).readString();
  StaticJsonDocument<256> doc;

  DeserializationError err = deserializeJson(doc,configJson);

  this->lastMessage = doc["lastMessage"].as<String>();

  if (err){
    Logger::error(err.f_str());
    return;
  }

}

void SettingsManager::saveSettingsToFile(){
  File configFile = SPIFFS.open(CONFIG_FILENAME,"w",true);
  StaticJsonDocument<256> doc;

  doc["lastMessage"] = this->lastMessage.c_str();

  String output = "";

  serializeJson(doc,output);

  configFile.print(output);

  configFile.close();
}

void SettingsManager::setLastMessage(String message){
  this->lastMessage = message;
  saveSettingsToFile();
}


SettingsManager* SettingsManager::getInstance(){
  if (!settingsManagerInstance) settingsManagerInstance = new SettingsManager();

  return settingsManagerInstance;
}

void SettingsManager::debug(){
  File configFile = SPIFFS.open(CONFIG_FILENAME,"r",true);
  
  Logger::log(configFile.readString());
  Logger::log(this->lastMessage);
}