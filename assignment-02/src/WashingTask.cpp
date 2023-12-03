#include "../lib/WashingTask.hpp"
#include "../lib/config.h"

extern bool startWashing;
extern bool washingFinished;
extern bool blinkStart500;

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
    if (this->sendUpdate)
    {
        Serial.println("washing routine");
        this->sendUpdate = false;
    }
    switch (this->currentState)
    {
    case WAITING_BUTTON:
        if (this->button->isPressed())
        {
            this->setState(WASHING);
            this->startTemp = -1;
            blinkStart500 = true;
        }
        break;
    case WASHING:
        Serial.println("Sono washing");
        this->sendWarning = true;
        this->fixFlag = false;
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
                    if (millis() - this->startTemp > N4)
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
        Serial.println("Sono error");
        if (this->sendWarning)
        {
            Serial.println("warning");
            this->sendWarning = false;
        }
        if (this->changeMsg)
        {
            this->lcd->showMessage("Detected a problem");
            this->changeMsg = false;
        }
        while (!fixFlag)
        {
            /* If there is something available in the serial line */
            if (Serial.available() == 1)
            {
                String answer = Serial.readStringUntil('\n');
                if (answer == "fix")
                {
                    this->setState(WASHING);
                    this->startTemp = -1;
                    this->fixFlag = true;
                }
            }
        }
        break;
    case END:
        this->lcd->showMessage("Washing complete you can leave!");
        startWashing = false;
        washingFinished = true;
        this->setActive(false);
        this->setState(WAITING_BUTTON);
        this->changeMsg = true;
        this->sendUpdate = true;
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
