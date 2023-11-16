#include "BlinkTask.hpp"

BlinkTask::BlinkTask(int pin) {
    this->pin = pin;
}

void BlinkTask::init(int period) {
    this->led = new Led(this->pin);
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