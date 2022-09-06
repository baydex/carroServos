

void giro(){
  
  int durationD = (velocidadD*intervalos) +  1000, durationI = (velocidadI*intervalos) +  1000;
  
  flag = micros();
  if(flag-times >= 20000){
    Serial.print(flag-times);
    Serial.print('-');
    Serial.print(velocidadD);
    Serial.print('-');
    Serial.println(velocidadI);
    times = micros();
  }
  else{
    if(flag-times<=durationD){
      digitalWrite(pinD,HIGH);
    } 
    else{
      digitalWrite(pinD,LOW);
    }
    if(flag-times<=durationI){
      digitalWrite(pinI,HIGH);
    } 
    else{
      digitalWrite(pinI,LOW);
    }  
  }
}


