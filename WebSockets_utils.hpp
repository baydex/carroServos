#include "servoController.hpp"

static const char INDEX_HTML[] PROGMEM = R"(
<!DOCTYPE html>                                                                       
<html>                                                                                
  <head>                                                                             
      <meta charset=utf-8>                                                            
      <meta name='viewport' content='initial-scale=1, maximum-scale=1'>               
                                                                                      
                                                                                      
      <title>WebSocket ESP8266 </title>                                
  </head>                                                                             
  <body>                                                                              
    
    
    <script>                 
     
      var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);                                                                                    
      connection.onopen = function () {      
        alert("conectado") ;                            
      }
      connection.onmessage = function (event) {                                      
        console.log('Servidor: ', event.data);                              
                                                                      
      }
      connection.onerror = function (error) {                                        
        console.log('F: ', error);                                    
      }
      
      function sendMessage(message){
      connection.send(message);
      }    
       
    </script>                                                                         
  </body>                                                                             
</html>
)";




void webSocketEvent(uint8_t num, WStype_t type, uint8_t* payload, size_t length){
  switch(type){
    case WStype_CONNECTED:{
      //myString = String(voltVal);
      //webSocket.sendTXT(num,myString);
      }
    break;
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Desconectado!\n", num);
    break;
    case WStype_TEXT:
      // Serial.printf("Número de conexión: %u - Caracteres recibidos: %s\n ", num, payload);
      // mover(payload,25);
      if(payload[0]>=64){
        velocidadI = payload[0]-64;       
      }
      else{
        velocidadD = payload[0];       
      }      
    break;
    case WStype_ERROR:
      Serial.printf("Se ha recibido un error. \n");
    break;
  }
}
