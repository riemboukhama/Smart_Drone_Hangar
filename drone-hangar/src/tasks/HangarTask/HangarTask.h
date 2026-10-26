#ifndef HANGARTASK_H
#define HANGARTASK_H
#include "../Task/Task.h"
#include "../../core/HangarContext/HangarContext.h"

class HangarTask : public Task {
private:
    HangarContext* ctx;
    unsigned long stateTimer; 
    bool timerStarted;
    
    const int D1 = 30; const int D2 = 15;
    const unsigned long T1 = 2000; const unsigned long T2 = 2000;
    
    void startTimer(); 
    void resetTimer(); 
    bool checkTimer(unsigned long targetTime);
public:
    HangarTask(HangarContext* context); 
    void tick() override;
};
#endif
