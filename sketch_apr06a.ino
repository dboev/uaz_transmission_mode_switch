#include "Button.h"
#include "Transmission.h"

//#define DEBUG

/*button on pin5, 1000 ms threshold, 3000ms BUTTON_PRESSED repeat period*/
Button button1(5, true, 1000, 100, 3000 );
Transmission transmission(2,3,4,6,7,8);

void setup() {

  #ifdef DEBUG
  Serial.begin(9600);
  #endif
  
}

void loop() {

  button1.updateState(); 
  transmission.updateState();  

  Event buttonEvent = button1.getEvent();

  if(buttonEvent == Event::BUTTON_DOWN || buttonEvent == Event::BUTTON_PRESSED) {    
    transmission.selectMode();     
  }

  if(buttonEvent == Event::BUTTON_UP) {
    if(transmission.getNextMode() != transmission.getMode()) {
      transmission.setMode(transmission.getNextMode());
    }
  }

  delay(10);


  
}
