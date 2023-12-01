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
    this->monitoringTimer = -1;
    this->setState(MONITORING);
}

void ProceedTask::tick()
{
    if (this->sendUpdate)
    {
        Serial.println("a car is entering");
        this->sendUpdate = false;
    }
    switch (this->currenState)
    {
    case MONITORING:
        if (this->changeMsg)
        {
            this->lcd->showMessage(this->proceedMessage);
            this->changeMsg = false;
        }
        if (this->sonar->getDistance() < MINDIST)
        {
            if (this->monitoringTimer == -1)
            {
                this->monitoringTimer = millis();
            }
            else
            {
                if (millis() - this->monitoringTimer > N2)
                {
                    this->setState(END);
                }
            }
        }
        else
        {
            this->monitoringTimer = -1;
        }
        break;
    case END:
        carEntered = true;
        canProceed = false;
        this->setActive(false);
        this->setState(MONITORING);
        this->changeMsg = true;
        this->monitoringTimer = -1;
        this->sendUpdate = true;
        break;
    }
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