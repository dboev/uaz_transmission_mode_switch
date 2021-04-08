#ifndef TRANSMISSION_H
#define TRANSMISSION_H


#define BLINK_TIME 125
#define BLINK_PERIOD 250

#define EEPROM_ADDL_L 0
#define EEPROM_ADDL_H 10

enum Mode {RWD, AWD_H, AWD_L};

class Transmission {
private:
    unsigned long blinkStartedTime;
    Mode nextMode;
    Mode mode;
    void updateLEDs();

    int ledRWD, ledAWD_H, ledAWD_L;
    Mode restoreModeFromEEPROM();
    void storeModeToEEPROM(Mode m);
    
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
