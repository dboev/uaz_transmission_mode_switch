#include <Arduino.h>
#include "Transmission.h"



Transmission::Transmission(int led2h, int led4h, int led4l, int out2h, int out4h, int out4l) {

  ledRWD   = led2h; 
  ledAWD_H = led4h; 
  ledAWD_L = led4l;

  mode = RWD;
  nextMode = RWD;
  
  updateState();
}



void Transmission::updateState(){

      

      int led2hState = LOW;
      int led4hState = LOW;
      int led4lState = LOW;

      switch(mode) {
        case Mode::RWD:   led2hState = HIGH;
                          break;

        case Mode::AWD_H: led4hState = HIGH;
                          break;
                          
        case Mode::AWD_L: led4lState = HIGH;
                          break;              
      }

    
   
   if(nextMode != mode) {
      unsigned long currentTime = millis();
     
      
      if (currentTime < blinkStartedTime) {
        blinkStartedTime = currentTime;
      }

      unsigned long d = (currentTime - blinkStartedTime) % BLINK_PERIOD;

      
    
      
      if ( d <= BLINK_TIME) {
          switch(nextMode) {
            case Mode::RWD:   led2hState = HIGH;
                              break;
    
            case Mode::AWD_H: led4hState = HIGH;
                              break;
                              
            case Mode::AWD_L: led4lState = HIGH;
                              break;              
          }        
      } 
   } 

   digitalWrite(ledRWD, led2hState);
   digitalWrite(ledAWD_H, led4hState); 
   digitalWrite(ledAWD_L, led4lState);

   

}
void Transmission::setMode(Mode newMode){

  #ifdef DEBUG
  
  Serial.print("switch mode :");
  switch(mode){
    case Mode::RWD:   Serial.print("RWD");   break;
    case Mode::AWD_H: Serial.print("AWD_H"); break;
    case Mode::AWD_L: Serial.print("AWD_L"); break;
  }

  #endif
  
  mode = newMode;
  nextMode = newMode;

  #ifdef DEBUG

  Serial.print(" -> ");
  switch(mode){
    case Mode::RWD:   Serial.println("RWD");   break;
    case Mode::AWD_H: Serial.println("AWD_H"); break;
    case Mode::AWD_L: Serial.println("AWD_L"); break;
  }

  #endif
}

void Transmission::setNextMode(Mode newMode){
  nextMode = newMode;
  blinkStartedTime = millis();

  #ifdef DEBUG
  Serial.print("next mode -> ");
  switch(nextMode){
    case Mode::RWD:   Serial.println("RWD");   break;
    case Mode::AWD_H: Serial.println("AWD_H"); break;
    case Mode::AWD_L: Serial.println("AWD_L"); break;
  }
  #endif
}


Mode Transmission::getMode(){
  return mode;
}

Mode Transmission::getNextMode(){
  return nextMode;
}


void Transmission::selectMode() {
  if(mode == Mode::RWD) {
    if(nextMode == Mode::RWD) {
      setNextMode(Mode::AWD_H);
    } else {
      setNextMode(Mode::RWD);
    }
  }

  if(mode == Mode::AWD_H) {
    if(nextMode == Mode::AWD_H) {
      setNextMode(Mode::RWD);
    } else {

      if(nextMode == Mode::RWD) {
        setNextMode(Mode::AWD_L);
      } else {
        setNextMode(Mode::AWD_H);
      }
    }
  }

  if(mode == Mode::AWD_L) {
    if(nextMode == Mode::AWD_L) {
      setNextMode(Mode::AWD_H);
    } else {
      setNextMode(Mode::AWD_L);
    }
  }
  
}
