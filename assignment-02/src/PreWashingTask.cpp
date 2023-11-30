#include "../lib/PreWashingTask.hpp"
#include "../lib/config.h"

extern bool canProceed;
extern bool carEntered;
extern bool startWashing;

PreWashingTask::PreWashingTask()
{
}

void PreWashingTask::init()
{
    Task::init(1);
    this->readyMessage = "Ready to Wash";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->lcd->clear();
    this->gate = new Gate(GATE_PIN);
    this->l2 = new Led(L2);
    this->l1 = new Led(L1);
}

void PreWashingTask::tick()
{
    Serial.println("prewashing routine");
    this->gate->on();
    this->gate->close();
    this->gate->off();
    this->l1->switchOff();
    this->l2->switchOn();
    this->lcd->showMessage(this->readyMessage);
    this->setActive(false);
    startWashing = true;
    carEntered = false;
}

bool PreWashingTask::isActive()
{
    if (carEntered)
    {
        this->setActive(true);
        return true;
    }
    return false;
}