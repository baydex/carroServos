#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "Server.hpp"
#include "ESP8266_Utils.hpp"




void setup(void) 
{
  // Pines
  pinMode(pinD, OUTPUT);
  pinMode(pinI, OUTPUT);  
  // Serial
  Serial.begin(115200);
  // Server
  ConnectWiFi_AP();
  InitServer();
}
 
void loop()
{
  webSocket.loop();
  server.handleClient();
  giro();  
}




