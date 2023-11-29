#include "../lib/PirDetectionTask.hpp"

extern bool startDetecting;
extern bool carDetected;

PirDetectionTask::PirDetectionTask(int pin) {
    this->pin = pin;
}

void PirDetectionTask::init(int period) {
    this->pir = new Pir(this->pin);
    this->l2 = new Led(L2);
    this->l2->switchOn();
    for (int i = 0; i < PIR_CALIBRATION_TIME; i++) {
        delay(1000);
    }
    this->l2->switchOff();
    Task::init(period);
}

void PirDetectionTask::tick() {
    Serial.println("looking for some cars");
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