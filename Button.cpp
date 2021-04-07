#include <Arduino.h>
#include "Button.h"


Button::Button(int pin, bool pullUpEnable, int thresholdPress, int thresholdRelease, int repeatInterval) {

  _pin = pin;
  _lastCheckedState = 0;
  _lastCheckedStateTime = millis();
  _buttonState = State::RELEASED;
  _event = NULL;
  _thresholdPress = thresholdPress;
  _thresholdRelease = thresholdRelease;
  _buttonPressedEventDuration = repeatInterval;
  
  pinMode(pin, INPUT);
  
  if(pullUpEnable) {
    pinMode(pin, INPUT_PULLUP);
  }
  
}


void Button::updateState(){
  int currentState = digitalRead(_pin);

  unsigned long currentMillis = millis();

  //millis overflow
  if(currentMillis < _lastCheckedStateTime) {    
    _lastCheckedStateTime = currentMillis;
    _lastButtonPressedEventTime = currentMillis;
    return;
  }
  
  if (currentState != _lastCheckedState) {
    _lastCheckedStateTime = currentMillis;
    
  } else {      

    unsigned int threshold = (_buttonState == State::RELEASED) ? _thresholdPress : _thresholdRelease;
        
    if(currentMillis >= _lastCheckedStateTime + threshold) {
      /*состояние кнопки не меняется дольше, чем _threshold*/                                                      
      if(currentState == 0 &&  _buttonState == State::RELEASED) {                                   // button pressed
        _buttonState = State::PRESSED;
        _event = Event::BUTTON_DOWN;
        _lastButtonPressedEventTime = currentMillis;
      } 
      
      if(currentState == 1 &&  _buttonState == State::PRESSED) {                                   // button released
        _buttonState = State::RELEASED;
        _event = Event::BUTTON_UP;
      }      
    }
  }
  _lastCheckedState = currentState;

  if ( (_buttonPressedEventDuration != 0) && (_buttonState == State::PRESSED) && (_event == Event::NONE) && (currentMillis >= _lastButtonPressedEventTime + _buttonPressedEventDuration)) {
    _event = Event::BUTTON_PRESSED;
    _lastButtonPressedEventTime = currentMillis;
  }
  
}



State Button::getState(){
  return _buttonState;
}

Event Button::getEvent(){
  Event event = _event;
  _event = Event::NONE;
  return event;
}
