#include "Scheduler.h"

Scheduler::Scheduler() {
    nTasks = 0;
}

bool Scheduler::addTask(Task* task) {
    if (nTasks < MAX_TASKS) {
        taskList[nTasks++] = task;
        return true;
    }
    return false;
}

void Scheduler::schedule() {
    for (int i = 0; i < nTasks; i++) {
        if (taskList[i]->updateAndCheckTime()) {
            taskList[i]->tick();
        }
    }
}
