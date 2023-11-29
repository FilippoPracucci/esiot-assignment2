#include "../lib/PirDetectionTask.hpp"

extern bool startDetecting;
extern bool carDetected;

PirDetectionTask::PirDetectionTask(int pin) {
    this->pin = pin;
}

void PirDetectionTask::init(int period) {
    this->pir = new Pir(this->pin);
    Task::init(period);
}

void PirDetectionTask::tick() {
    if (this->pir->detect()) {
        //Serial.println("Trovata una macchina");
        carDetected = true;
        this->setActive(false);
    }
    startDetecting = false;
}

bool PirDetectionTask::isActive() {
    if (startDetecting) {
        this->setActive(true);
        return true;
    }
    return false;
}