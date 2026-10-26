#ifndef TEMPTASK_H
#define TEMPTASK_H
#include "../Task/Task.h"
#include "../../core/HangarContext/HangarContext.h"

class TempTask : public Task {
private:
    HangarContext* ctx;
    unsigned long timerTemp1; unsigned long timerTemp2;
    const unsigned long T3 = 3000; const unsigned long T4 = 3000;
    const float Temp1 = 38.0; const float Temp2 = 40.0;
public: 
    TempTask(HangarContext* context); 
    void tick() override;
};
#endif
