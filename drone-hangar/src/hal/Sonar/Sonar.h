#ifndef SONAR_H
#define SONAR_H
#include <Arduino.h>
class Sonar {
private: 
    int trigPin; 
    int echoPin;
public: 
    Sonar(int trig, int echo); 
    long getDistance();
};
#endif
