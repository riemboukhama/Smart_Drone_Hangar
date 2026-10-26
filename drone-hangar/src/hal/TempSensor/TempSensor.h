#ifndef TEMPSENSOR_H
#define TEMPSENSOR_H
#include <Arduino.h>
class TempSensor {
private: 
    int pin;
public: 
    TempSensor(int p); 
    float getTemperature();
};
#endif
