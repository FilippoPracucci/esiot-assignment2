#include "../lib/PirDetectionTask.hpp"

extern bool carDetected;

PirDetectionTask::PirDetectionTask(int pin) {
    this->pin = A0;
}

void PirDetectionTask::init(int period) {
    this->pir = new Pir(this->pin);
    Task::init(period);
}

void PirDetectionTask::tick() {
    if (this->pir->detect()) {
        Serial.println("Trovata una macchina");
        carDetected = true;
        this->setActive(false);
    }
}