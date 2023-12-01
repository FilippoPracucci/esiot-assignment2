#ifndef __TASK__
#define __TASK__

#include <Arduino.h>

class Task
{

public:
    
    int state;
    long stateTime;

    virtual void init(int period)
    {
        this->period = period;
        this->timeElapsed = 0;
        this->active = false;
    }

    virtual void init()
    {
    }

    virtual void tick() = 0;

    bool updateAndCheckTime(int generalPeriod)
    {
        this->timeElapsed += generalPeriod;
        if (this->timeElapsed >= this->period)
        {
            this->timeElapsed = 0;
            return true;
        }
        else
        {
            return false;
        }
    }

    virtual bool isActive()
    {
        return this->active;
    }

    void setActive(bool state)
    {
        this->active = state;
    }

    void setState(int s)
    {
        this->state = s;
        this->stateTime = millis();
    }

    long elapsedTime()
    {
        return millis() - this->stateTime;
    }

private:
    int period;
    int timeElapsed;
    bool active;
};

#endif
