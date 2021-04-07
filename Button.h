#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

enum State {PRESSED, RELEASED};
enum Event {NONE, BUTTON_UP, BUTTON_DOWN, BUTTON_PRESSED};

class Button {
 private:
    int _pin;
    unsigned long _lastCheckedStateTime;
    int _lastCheckedState;
    unsigned int _thresholdPress, _thresholdRelease;
    int _buttonPressedEventDuration;
    unsigned long _lastButtonPressedEventTime;

    State _buttonState;
    Event _event;
     
 public:


  
    Button(int pin, bool pullUpEnable, int thresholdPress, int thresholdRelease, int repeatInterval );
    void updateState();
    State getState();
    Event getEvent();
};
#endif
