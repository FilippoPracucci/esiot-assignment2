#ifndef __PIRDETECTIONTASK__
#define __PIRDETECTIONTASK__

#include "Pir.hpp"
#include "Task.hpp"
#include "Led.hpp"
#include "config.h"
#include <avr/sleep.h>

class PirDetectionTask : public Task {

public:
    PirDetectionTask(int pin);
    void init(int period);
    void tick();
    bool isActive() override;
    void wake();

private:
    int pin;
    Pir* pir;
    Led *l2;
};

#endif