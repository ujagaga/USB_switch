#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Servo.h>
#include "udp_client.h"
#include "config.h"
#include "ota.h"

#define STATE_TIME  (100)

ESP8266WiFiMulti WiFiMulti;
uint32_t switching_time = 0;
static int port = 1;
static int next_port = 0;

void check_port(){  

  if(switching_time == 0){
    next_port = UDPC_getPort();
    if(next_port != port){
      Serial.print ( "New port:" );
      Serial.println ( next_port );
      switching_time = millis();
    }
  }else{
    uint32_t period = millis() - switching_time;

    if(period < STATE_TIME){
      if(port == 0){
        digitalWrite(USB1_DATA_PIN, LOW);
      }else{
        digitalWrite(USB2_DATA_PIN, LOW);
      }
      
    }else if(period < (2 * STATE_TIME)){
      if(port == 0){
        digitalWrite(USB1_PWR_PIN, LOW);
      }else{
        digitalWrite(USB2_PWR_PIN, LOW);
      }
      port = next_port;
      
    }else if(period < (3 * STATE_TIME)){
      if(port == 0){
        digitalWrite(USB1_PWR_PIN, HIGH);
      }else{
        digitalWrite(USB2_PWR_PIN, HIGH);
      }
      
    }else if(period < (4 * STATE_TIME)){
      if(port == 0){
        digitalWrite(USB1_DATA_PIN, HIGH);
      }else{
        digitalWrite(USB2_DATA_PIN, HIGH);
      }
      
    }else{
      switching_time = 0;
    }    
  }
}

void setup()
{
  pinMode(USB1_PWR_PIN, OUTPUT);
  digitalWrite(USB1_PWR_PIN, LOW);
  pinMode(USB1_DATA_PIN, OUTPUT);
  digitalWrite(USB1_DATA_PIN, LOW);
  pinMode(USB2_PWR_PIN, OUTPUT);
  digitalWrite(USB2_PWR_PIN, LOW);
  pinMode(USB2_DATA_PIN, OUTPUT);
  digitalWrite(USB2_DATA_PIN, LOW);
    
  Serial.begin(115200);
   
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(SSID_1, PASS_1);
  WiFiMulti.addAP(SSID_2, PASS_2);
 
  Serial.print( "\n\nConnecting" );
  while ( WiFiMulti.run() != WL_CONNECTED ) {
    delay ( 500 );
    ESP.wdtFeed();
    Serial.print ( "." );    
  }
  String IP =  WiFi.localIP().toString();
  String wifi_statusMessage = "\nConnected to: " + WiFi.SSID() + String(". IP address: ") + IP;   
  Serial.println(wifi_statusMessage);  

  UDPC_init();
  switching_time = millis();  // Force start USB1
}

void loop() {  
  if(OTA_updateInProgress()){
    OTA_process();
  }else{
    UDPC_process();
    check_port();
  }
}
