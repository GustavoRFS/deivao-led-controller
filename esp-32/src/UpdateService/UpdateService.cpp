#include <Update.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <FS.h>
#include "UpdateService.h"
#include "Utils/Utils.h"

#include "definitions.h"

#ifdef USE_LITTLEFS
#define SPIFFS LITTLEFS
#include <LITTLEFS.h>
#else
#include <SPIFFS.h>
#endif

bool *hasUpdates = NULL;

void UpdateService::setup()
{
}


// void UpdateService::update()
// {
//   Assets *assets = getAllUpdateAssets();
//   xTaskCreate([](void *params)
//               {
//     Assets* assets = (Assets*) params;

//     File updateLock = SPIFFS.open("/update.lck","w",true);
//     updateLock.print(assets->version);
//     updateLock.close();

//     String assetUrl = "";

//     for (uint8_t i=0;i<assets->size;i++) {
//       if (assets->assets[i].name=="firmware.bin") assetUrl = assets->assets[i].url;
//     }

//     if (!Update.begin(UPDATE_SIZE_UNKNOWN)){
//       Update.printError(Serial);
//     }

//     String downloadURL=Utils::getDownloadURL(assetUrl);

//     HTTPClient http;

//     http.begin(downloadURL);
//     http.useHTTP10(true);
//     int code = http.GET();

//     if (code!=200) return;

//     AsyncWebSocket* ws = ControllerWS::WebSocket();

//     bool sendMessage = ws->count()>0;

//     Utils::handleStream(http,[sendMessage,ws](uint8_t* buff,size_t size,size_t remaining,size_t total){
//       Update.write(buff,size);

//       if (sendMessage) ws->textAll("{\"event\":\"updating\",\"data\":{\"name\":\"firmware\",\"percentage\":"+String((float(total-remaining)/total)*100)+"}}");
//     });

//     Update.end(true);

//     if (Update.hasError()){
//       ws->textAll("{\"event\":\"updateError\",\"data\":\"Erro: " + String(Update.errorString())+"\"}");
//     }
//     else {
//       ws->textAll("{\"event\":\"updating\",\"data\":{\"name\":\"firmware\",\"percentage\":100}}");
//       Utils::delay(500);
//       ESP.restart();
//     }

//     delete assets;

//     vTaskDelete(NULL); },
//               "Download assets", 10000, (void *)assets, 1, NULL);
// }