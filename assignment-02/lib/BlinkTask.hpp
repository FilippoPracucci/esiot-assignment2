#ifndef __BLINKTASK__
#define __BLINKTASK__

#include "Task.hpp"
#include "Led.hpp"

class BlinkTask : public Task {

public:
    BlinkTask();
    void init(int period);
    void tick();

private:
    int pin;
    Led* led;
    enum { ON, OFF } state;
};

#endif