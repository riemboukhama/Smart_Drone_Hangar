#ifndef TASK_H
#define TASK_H
#include <Arduino.h>
class Task {
protected: 
    int myPeriod; 
    unsigned long timeElapsed; 
    unsigned long lastTime;
public:
    virtual void init(int period) { myPeriod = period; timeElapsed = 0; lastTime = millis(); }
    virtual void tick() = 0;
    bool updateAndCheckTime() {
      unsigned long currentTime = millis();
      timeElapsed += (currentTime - lastTime);
      lastTime = currentTime;
      if (timeElapsed >= myPeriod) { timeElapsed = 0; return true; }
      return false;
    }
};
#endif
