#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include "udp_client.h"
#include "config.h"
#include "ota.h"

static WiFiUDP Udp;                             /* UDP object used for receiving the ping message. */
static char incomingPacket[10];                 /* buffer for incoming packets */
static int port = 0;

void UDPC_init(){
  Udp.begin(UDP_PORT);
}

void UDPC_process(){
  int packetSize = Udp.parsePacket();
  
  if((packetSize > 0) && (packetSize < 10)){
    // receive incoming UDP packets
    int len = Udp.read(incomingPacket, 10);
    
    incomingPacket[len] = 0;

    String msg = String(incomingPacket);  
    Serial.print("RX:");
    Serial.println(msg);
    if(msg == "ota"){
      OTA_init();
    }else{    
    
      int rx = msg.toInt();

      if((rx > 199) && (rx < 202)){
        if(rx == 200){
          port = 0;
        }else{
          port = 1;
        }
      }    
    }
  }
}

int UDPC_getPort(){ 
  return port;
}
