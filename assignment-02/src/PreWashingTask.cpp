#include "../lib/PreWashingTask.hpp"
#include "../lib/config.h"

extern bool blinkStart;
extern bool carEntered;
extern bool startWashing;

PreWashingTask::PreWashingTask() {
    
}

void PreWashingTask::init() {
    Task::init(1);
    this->readyMessage = "Ready to Wash";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->lcd->clear();
    this->gate = new Gate(GATE_PIN);
    this->l2 = new Led(L2);
    this->l1 = new Led(L1);
}

void PreWashingTask::tick() {
    Serial.println("prewashing routine");
    //Serial.println("inizio tick prewashing");
    this->gate->on();
    this->gate->close();
    this->gate->off();
    /* blinkStart = false; */
    this->l1->switchOff();
    this->l2->switchOn();
    carEntered = false;
    this->lcd->showMessage(this->readyMessage);
    startWashing = true;
    this->setActive(false);
    //Serial.println("fine tick prewashing");
}

bool PreWashingTask::isActive() {
    if (carEntered) {
        this->setActive(true);
        return true;
    }
    return false;
}