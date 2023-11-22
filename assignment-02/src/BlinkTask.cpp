#include "../lib/BlinkTask.hpp"
#include "../lib/config.h"

extern bool blinkStart;

BlinkTask::BlinkTask() {}

void BlinkTask::init(int period) {
    this->led = new Led(L2);
    Task::init(period);
    this->state = OFF;
}

void BlinkTask::tick() {
    switch (this->state) {
        case ON:
            this->led->switchOff();
            this->state = OFF;
            break;
        case OFF:
            this->led->switchOn();
            this->state = ON;
            break;
    }
}

bool BlinkTask::isActive() {
    if (blinkStart) {
        this->setActive(true);
        return true;
    }
    return false;
}