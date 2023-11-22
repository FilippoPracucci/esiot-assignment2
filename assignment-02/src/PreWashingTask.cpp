#include "../lib/PreWashingTask.hpp"
#include "../lib/config.h"

extern bool blinkStart;
extern bool carEntered;

PreWashingTask::PreWashingTask() {
    
}

void PreWashingTask::init() {
    this->readyMessage = "Ready to Wash";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->lcd->clear();
    this->gate = new Gate(GATE_PIN);
    this->l2 = new Led(L2);
}

void PreWashingTask::tick() {
    this->gate->on();
    this->gate->close();
    this->gate->off();
    blinkStart = false;
    this->l2->switchOn();
    carEntered = true;
    this->lcd->showMessage(this->readyMessage);
    this->setActive(false);
}

bool PreWashingTask::isActive() {
    if (carEntered) {
        this->setActive(true);
        return true;
    }
    return false;
}