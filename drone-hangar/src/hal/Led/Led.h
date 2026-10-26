#ifndef LED_H
#define LED_H
#include <Arduino.h>
class Led {
private: 
    int pin; 
    bool state;
public: 
    Led(int p); 
    void turnOn(); 
    void turnOff(); 
    void toggle();
};
#endif
