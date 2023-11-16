#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.hpp"
#include <LinkedList.h>

class Scheduler {

public:
    void init(int period);
    virtual void addTask(Task* task);
    virtual void schedule();

private:
    int generalPeriod;
    LinkedList<Task*> taskList;
};

#endif