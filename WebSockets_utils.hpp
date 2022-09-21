#include "servoController.hpp"

static const char INDEX_HTML[] PROGMEM = R"(
<!DOCTYPE html>                                                                       
<html style="width: 100%; height: 100%; margi:0; padding:0;">                                                                                
  <head>                                                                             
      <meta charset=utf-8>                                                            
      <meta name='viewport' content='initial-scale=1, maximum-scale=1'>               
                                                                                      
                                                                                      
      <title>Control Carro ESP8266</title>                                
  </head>                                                                             
  <body style="width: 100%; height: 100%; margin:0; padding:0;"> 
      <div id="m1"></div>                       
      <div id="m2"></div>                                                      
      <div class="control" style="width: 100%; height: 90%; display: flex; justify-content: center; align-items: center;">
        <div class="controlContainer" style="display: flex;">
          <div class="acelerador" style="width: 200px; height: 200px; display: flex; justify-content: center; align-items: center;">
            <input type="range" name="" id="acelerador" step="1" min="0" max="12" value="0">
          </div>
          <div class="botones" style="width: 180px; height: 180px; display: flex; justify-content: space-around; align-items: center;">
            <div class="left">
              <div id="left" style="padding: 20px; border-radius: 50%; background-color: black; color: white; user-select: none;"> < </div>
            </div>
            <div class="center" style="display: flex; flex-direction: column; justify-content: space-around; height: 200px;">
              <div id="up" style="padding: 20px; border-radius: 50%; background-color: black; color: white; user-select: none;"> ^ </div>
              <div id="down" style="padding: 20px; border-radius: 50%; background-color: black; color: white; user-select: none;"> v </div>
            </div>
            <div class="right">
              <div id="right" style="padding: 20px; border-radius: 50%; background-color: black; color: white; user-select: none;"> > </div>
            </div>
          </div>
        </div>
      </div>

    <script>         
      acelerador = document.getElementById("acelerador");
      up = document.getElementById("up");
      down = document.getElementById("down");
      left = document.getElementById("left");
      right = document.getElementById("right");
      m1 = document.getElementById("m2");
      m2 = document.getElementById("m1");
      
      let code = (value)=>{return String.fromCharCode(value)}
      let velocidad = parseInt(acelerador.value)
      let selected = null

      acelerador.addEventListener('input',()=>{
        velocidad = parseInt(acelerador.value);
        if(selected){
          if(selected==up){
            tU();
          }
          else if(selected==down){
            tD();
          }
          else if(selected==left){
            tL();
          }
          else if(selected==right){
            tR();
          }
        }
      })        
      
      up.addEventListener("touchstart",tU)
      down.addEventListener("touchstart",tD)
      left.addEventListener("touchstart",tL)
      right.addEventListener("touchstart",tR)
      up.addEventListener("touchend",()=>{
        selected = null;
        direccion(13,13);
      })
      down.addEventListener("touchend",()=>{
        selected = null;
        direccion(13,13);
      })
      left.addEventListener("touchend",()=>{
        selected = null;
        direccion(13,13);
      })
      right.addEventListener("touchend",()=>{
        selected = null;
        direccion(13,13);
      })

      function tU(){
        selected = up;
        mLeft = 13 + velocidad;
        mRight = 13 - velocidad-1;
        direccion(mLeft,mRight);
      }
      function tD(){
        selected = down;
        mLeft = 13 - velocidad-1;
        mRight = 13 + velocidad;
        direccion(mLeft,mRight);
      }
      function tR(){
        selected = right;
        mLeft = 13 + velocidad;
        mRight = 13 + velocidad;
        direccion(mLeft,mRight);
      }
      function tL(){
        selected = right;
        mLeft = 13 - velocidad - 1;
        mRight = 13 - velocidad - 1;
        direccion(mLeft,mRight);
      }

      function direccion(mLeft, mRight){
        console.log(mLeft,mRight+64)
        m1.textContent = mLeft
        m2.textContent = mRight+64
        sendMessage(code(mLeft))
        sendMessage(code(mRight+64))
      }

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
