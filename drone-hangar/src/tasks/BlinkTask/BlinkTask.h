#ifndef BLINKTASK_H
#define BLINKTASK_H
#include "../Task/Task.h"
#include "../../core/HangarContext/HangarContext.h"

class BlinkTask : public Task { 
private:
    HangarContext* ctx;
public: 
    BlinkTask(HangarContext* context);
    void tick() override; 
};
#endif
