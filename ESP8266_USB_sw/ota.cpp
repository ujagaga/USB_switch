/* 
 *  Author: Rada Berar
 *  email: ujagaga@gmail.com
 *  
 *  Over The Air update module.
 *  
 *  Arduino Studio offers OTA update. You can choose the device like you choose the serial port.
 *  NOTE: After uploading code via UART, make sure to restart the device before atempting OTA.
 */
#include <ArduinoOTA.h>
#include "config.h"

static bool updateStartedFlag = false;

bool OTA_updateInProgress(){
  return updateStartedFlag;
}

void OTA_init() {

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);
  ArduinoOTA.setHostname(DEVICE_NAME);

  // No authentication by default
  //ArduinoOTA.setPassword((const char *)"pass123");
   
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH)
      type = "sketch";
    else // U_SPIFFS
      type = "filesystem";

    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    updateStartedFlag = false;
    ESP.restart();
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {    
  });
  ArduinoOTA.onError([](ota_error_t error) {   
  });
  ArduinoOTA.begin();

  updateStartedFlag = true;
}

void OTA_process(void){
  ArduinoOTA.handle();
}
