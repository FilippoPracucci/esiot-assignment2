#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"
#include "../lib/BlinkTask.hpp"

extern bool carDetected;

WelcomeTask::WelcomeTask() {}

void WelcomeTask::init() {
    this->welcomeMessage = "Welcome";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS); //address in config file to change in hexadecimal
    this->gate = new Gate(GATE_PIN);
    this->l1 = new Led(L1);
    this->blinkTask = new BlinkTask();
    this->blinkTask->init(BLINK_PERIOD_START);
}

void WelcomeTask::tick() {

    this->l1->switchOn();
    this->lcd->showMessage(this->welcomeMessage);
    delay(N1);
    this->gate->open();
    this->blinkTask->setActive(true);
}

bool WelcomeTask::isActive() {
    if (carDetected) {
        this->setActive(true);
        return true;
    }
    return false;
}