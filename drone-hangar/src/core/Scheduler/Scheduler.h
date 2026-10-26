#ifndef SCHEDULER_H
#define SCHEDULER_H
#include "../../tasks/Task/Task.h"

#define MAX_TASKS 10

class Scheduler {
private:
    int nTasks;
    Task* taskList[MAX_TASKS];
public:
    Scheduler();
    bool addTask(Task* task);
    void schedule();
};
#endif
