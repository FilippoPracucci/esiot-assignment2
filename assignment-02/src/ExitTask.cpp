#include "../lib/ExitTask.hpp"
#include "../lib/config.h"

extern bool washingFinished;
extern bool startDetecting;
extern int completedWashing;
ExitTask::ExitTask()
{
}

void ExitTask::init()
{
    Task::init(1);
    this->l2 = new Led(L2);
    this->l3 = new Led(L3);
    this->gate = new Gate(GATE_PIN);
    this->sonar = new Sonar(ECHO_PIN, TRIG_PIN);
    this->setState(OPEN);
}

void ExitTask::tick()
{
    if (this->sendUpdate)
    {
        Serial.println("washing finished, car is exiting");
        this->sendUpdate = false;
    }
    switch (this->currenState)
    {
    case OPEN:
        this->l2->switchOff();
        this->l3->switchOn();
        this->gate->on();
        this->gate->open();
        this->gate->off();
        this->monitoringTimer = -1;
        this->setState(DETECTING);
        break;
    case DETECTING:
        if (this->sonar->getDistance() > MAXDIST)
        {
            if (this->monitoringTimer == -1)
            {
                this->monitoringTimer = millis();
            }
            else
            {
                if (millis() - this->monitoringTimer > N4)
                {
                    this->setState(CLOSE);
                }
            }
        }
        else
        {
            this->monitoringTimer = -1;
        }
        break;
    case CLOSE:
        this->gate->on();
        this->gate->close();
        this->gate->off();
        this->l3->switchOff();
        Serial.println(String(++completedWashing));
        startDetecting = true;
        washingFinished = false;
        this->setActive(false);
        this->setState(OPEN);
        this->sendUpdate = true;
        break;
    }
}

bool ExitTask::isActive()
{
    if (washingFinished)
    {
        this->setActive(true);
        return true;
    }
    return false;
}