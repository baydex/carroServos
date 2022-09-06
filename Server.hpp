#include "WebSockets_utils.hpp"

WebSocketsServer webSocket = WebSocketsServer(81);
ESP8266WebServer server(80);

void handleRoot() 
{
   server.send_P(200, "text/html", INDEX_HTML);
}

void handleNotFound() 
{
   server.send(404, "text/plain", "Not found");
}

void InitServer()
{
   webSocket.begin();
   webSocket.onEvent(webSocketEvent);

   server.on("/", handleRoot);
  
   server.onNotFound(handleNotFound);
 
   server.begin();
   Serial.println("HTTP server started");
}
