#include "../lib/BlinkTask.hpp"
#include "../lib/config.h"

extern bool blinkStart500;
extern bool blinkStart100;

BlinkTask::BlinkTask() {}

void BlinkTask::init(int period)
{
    this->led = new Led(L2);
    Task::init(period);
    this->setState(OFF);
    this->period = period;
}

void BlinkTask::tick()
{
    switch (this->currentState)
    {
    case ON:
        if (this->elapsedTime() > this->period)
        {
            this->led->switchOff();
            this->setState(OFF);
            break;
        }
    case OFF:
        if (this->elapsedTime() > this->period)
        {
            this->led->switchOn();
            this->setState(ON);
            break;
        }
    }
}

bool BlinkTask::isActive()
{
    if ((blinkStart500 && !blinkStart100) || (blinkStart100 && !blinkStart500))
    {
        this->setActive(true);
        return true;
    }
    return false;
}