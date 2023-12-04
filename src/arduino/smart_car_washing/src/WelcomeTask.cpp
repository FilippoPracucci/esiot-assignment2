#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"

extern bool carDetected;
extern bool canProceed;
extern bool blinkStart100;

WelcomeTask::WelcomeTask()
{
}

void WelcomeTask::init(int period)
{
    Task::init(period);
    this->welcomeMessage = "Welcome";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS); // address in config file to change in hexadecimal
    this->lcd->clear();
    this->gate = new Gate(GATE_PIN);
    this->l1 = new Led(L1);
    this->sendUpdate = true;
    this->setState(START);
}

void WelcomeTask::tick()
{
    if (this->sendUpdate)
    {
        Serial.println("car detected, welcome routine");
        this->sendUpdate = false;
    }
    switch (this->currentState)
    {
    case START:
        this->l1->switchOn();
        this->lcd->showMessage(this->welcomeMessage);
        blinkStart100 = true;
        this->setState(WAITING);
        break;
    case WAITING:
        if (elapsedTime() > N1)
        {
            this->setState(END);
        }
        break;
    case END:
        this->gate->on();
        this->gate->open();
        this->gate->off();
        this->setActive(false);
        canProceed = true;
        carDetected = false;
        this->sendUpdate = true;
        this->setState(START);
        break;
    }

    delay(N1);
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