#ifndef TRANSMISSION_H
#define TRANSMISSION_H


#define BLINK_TIME 125
#define BLINK_PERIOD 250

enum Mode {RWD, AWD_H, AWD_L};

class Transmission {
private:
    unsigned long blinkStartedTime;
    Mode nextMode;
    Mode mode;
    void updateLEDs();

    int ledRWD, ledAWD_H, ledAWD_L;
    
public:
    Transmission(int led2h, int led4h, int led4L, int out2h, int out4h, int out4l);
    void updateState();    
    void setMode(Mode newMode);
    void setNextMode(Mode newMode);
    Mode getMode();
    Mode getNextMode();
    void selectMode();
};



#endif
