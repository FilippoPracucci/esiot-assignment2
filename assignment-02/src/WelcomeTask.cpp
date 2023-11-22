#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"
#include "../lib/BlinkTask.hpp"

extern bool carDetected;

WelcomeTask::WelcomeTask(Task* blinkTask) {
    this->blinkTask = blinkTask;
}

void WelcomeTask::init(int periodo) {
    this->welcomeMessage = "Welcome";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS); //address in config file to change in hexadecimal
    this->lcd->clear();
    this->gate = new Gate(GATE_PIN);
    this->l1 = new Led(L1);
}

void WelcomeTask::tick() {
    this->l1->switchOn();
    this->lcd->showMessage(this->welcomeMessage);
    delay(N1);
    this->gate->on();
    this->gate->open();
    delay(2000);
    this->gate->close();
    this->gate->off();
    this->blinkTask->setActive(true);
    this->setActive(false);
    carDetected =  false;
}

bool WelcomeTask::isActive() {
    if (carDetected) {
        this->setActive(true);
        return true;
    }
    return false;
}