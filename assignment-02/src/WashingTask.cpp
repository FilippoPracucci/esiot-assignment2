#include "../lib/WashingTask.hpp"
#include "../lib/config.h"

extern bool startWashing;
extern bool washingFinished;

WashingTask::WashingTask()
{
}

void WashingTask::init()
{
    Task::init(1);
    this->button = new Button(BUTTON_PIN);
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->l2 = new BlinkingLed(L2);
    this->tmp = new Tmp(TMP_PIN);
    this->setState(WAITING_BUTTON);
    this->startTemp = -1;
}

void WashingTask::tick()
{
    Serial.println("washing routine");
    switch (this->state)
    {
    case WAITING_BUTTON:
        if (this->button->isPressed())
        {
            this->setState(WASHING);
            this->startTemp = -1;
        }
        break;
    case WASHING:
        if (this->elapsedTime() > N3)
        {
            this->setState(END);
        }
        else
        {
            float temperature = this->tmp->detect();
            int progressPerc = map((N3 - (millis() - this->stateTime)), 0, 10000, 0, 100);
            this->lcd->printBar(progressPerc);
            Serial.println("temp" + String(temperature));
            if (temperature > MAXTEMP)
            {
                if (this->startTemp == -1)
                {
                    this->startTemp = millis();
                }
                else
                {
                    if (millis() -  this->startTemp > N4)
                    {
                        this->setState(ERROR);
                    }
                }
            }
            else
            {
                this->startTemp = -1;
            }
        }
        break;
    case ERROR:
        Serial.println("warning");
        this->lcd->showMessage("Detected a problem");
        /* If there is something available in the serial line */
        if (Serial.available() == 1)
        {
            String answer = Serial.readStringUntil('\n');
            if (answer == "fix")
            {
                this->setState(WASHING);
                this->startTemp = -1;
            }
        }
        break;
    case END:
        this->lcd->showMessage("Washing complete you can leave!");
        startWashing = false;
        washingFinished = true;
        this->setActive(false);
        break;
    }
}

bool WashingTask::isActive()
{
    if (startWashing)
    {
        this->setActive(true);
        return true;
    }
    return false;
}
