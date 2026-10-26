#ifndef SERIALTASK_H
#define SERIALTASK_H
#include "../Task/Task.h"
#include "../../core/HangarContext/HangarContext.h"

class SerialTask : public Task { 
private:
    HangarContext* ctx;
public: 
    SerialTask(HangarContext* context);
    void tick() override; 
};
#endif
