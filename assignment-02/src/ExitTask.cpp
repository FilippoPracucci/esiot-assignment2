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
}

void ExitTask::tick()
{
    Serial.println("washing finished, car is exiting");
    this->l2->switchOff();
    this->l3->switchOn();
    this->gate->on();
    this->gate->open();
    this->gate->off();
    unsigned long start = millis();
    unsigned long delta;
    while ((millis() - start) < N4)
    {
        delta = millis();
        while ((millis() - delta) < 500)
        {
        }
        if (this->sonar->getDistance() < MAXDIST)
        {
            start = millis();
        }
    }
    this->gate->on();
    this->gate->close();
    this->gate->off();
    this->l3->switchOff();

    Serial.println(String(++completedWashing));

    startDetecting = true;
    washingFinished = false;
    this->setActive(false);
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