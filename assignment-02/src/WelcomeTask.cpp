#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"
#include "../lib/BlinkTask.hpp"

extern bool carDetected;
extern bool blinkStart;

WelcomeTask::WelcomeTask(Task* blinkTask) {
    /* this->blinkTask = blinkTask; */
}

void WelcomeTask::init() {
    this->welcomeMessage = "Welcome";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS); //address in config file to change in hexadecimal
    this->lcd->clear();
    this->gate = new Gate(GATE_PIN);
    this->l1 = new Led(L1);
}

void WelcomeTask::tick() {
    Serial.println("Inizio tick di welcomeTask");
    this->l1->switchOn();
    this->lcd->showMessage(this->welcomeMessage);
    delay(N1);
    this->gate->on();
    this->gate->open();
    this->gate->off();
    /* this->blinkTask->setActive(true); */
    this->setActive(false);
    blinkStart = true;
    carDetected =  false;
}

bool WelcomeTask::isActive() {
    if (carDetected) {
        this->setActive(true);
        return true;
    }
    return false;
}