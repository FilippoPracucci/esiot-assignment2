#include "../lib/ProceedTask.hpp"
#include "../lib/config.h"

extern bool carEntered;
extern bool canProceed;

ProceedTask::ProceedTask()
{
}

void ProceedTask::init()
{
    Task::init(1);
    this->proceedMessage = "Proceed to the Washing Area";
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->lcd->clear();
    this->sonar = new Sonar(ECHO_PIN, TRIG_PIN);
    this->l2 = new BlinkingLed(L2);
}

void ProceedTask::tick()
{
    Serial.println("a car is entering");
    this->lcd->showMessage(this->proceedMessage);
    unsigned long start = millis();
    unsigned long delta;
    while ((millis() - start) < N2)
    {
        delta = millis();
        this->l2->blink(BLINK_PERIOD_START);
        while ((millis() - delta) < 300)
        {
        }
        if (this->sonar->getDistance() > MINDIST)
        {
            start = millis();
        }
    }
    carEntered = true;
    canProceed = false;
    this->setActive(false);
}

bool ProceedTask::isActive()
{
    if (canProceed)
    {
        this->setActive(true);
        return true;
    }
    return false;
}