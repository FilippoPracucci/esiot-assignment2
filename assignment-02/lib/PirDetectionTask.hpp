#ifndef __PIRDETECTIONTASK__
#define __PIRDETECTIONTASK__

#include "Pir.hpp"
#include "Task.hpp"

class PirDetectionTask : public Task {

public:
    PirDetectionTask(int pin);
    void init(int period);
    void tick();

private:
    int pin;
    Pir* pir;
};

#endif