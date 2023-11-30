#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"

extern bool carDetected;
extern bool canProceed;

WelcomeTask::WelcomeTask()
{
}

void WelcomeTask::init()
{
    Task::init(1);
    this->welcomeMessage = "Welcome";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS); // address in config file to change in hexadecimal
    this->lcd->clear();
    this->gate = new Gate(GATE_PIN);
    this->l1 = new Led(L1);
}

void WelcomeTask::tick()
{
    Serial.println("car detected, welcome routine");
    this->l1->switchOn();
    this->lcd->showMessage(this->welcomeMessage);
    delay(N1);
    this->gate->on();
    this->gate->open();
    this->gate->off();
    this->setActive(false);
    canProceed = true;
    carDetected = false;
}

bool WelcomeTask::isActive()
{
    if (carDetected)
    {
        this->setActive(true);
        return true;
    }
    return false;
}