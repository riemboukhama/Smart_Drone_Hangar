#ifndef HANGARDOOR_H
#define HANGARDOOR_H
#include <Arduino.h>
#include <Servo.h>
class HangarDoor {
private: 
    Servo servo; 
    int pin;
public: 
    HangarDoor(int p); 
    void init(); 
    void open(); 
    void close();
};
#endif
