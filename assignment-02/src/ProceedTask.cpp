#include "../lib/ProceedTask.hpp"
#include "../lib/config.h"

extern bool carEntered;
extern bool blinkStart;

ProceedTask::ProceedTask() {

}

void ProceedTask::init() {
    this->proceedMessage = "Proceed to the Washing Area";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->lcd->clear();
    this->sonar = new Sonar(ECHO_PIN, TRIG_PIN);
}

void ProceedTask::tick() {
    Serial.println("inizio tick proceed");
    this->lcd->showMessage(this->proceedMessage);
    unsigned long start = millis();
    unsigned long delta;
    while ((millis() - start) < N2) {
        Serial.println("Sono nel while");
        delta = millis();
        while ((millis() - delta) < 500) {}
        if (this->sonar->getDistance() > MINDIST) {
            Serial.println("Ho trovato una distanza maggiore a minDist");
            start = millis();
        }
    }
    carEntered = true;
    blinkStart = false;
    this->setActive(false);
    Serial.println("fine tick proceed");
}

bool ProceedTask::isActive() {
    if (blinkStart) {
        this->setActive(true);
        return true;
    }
    return false;
}