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
}

void WashingTask::tick()
{
    Serial.println("washing routine");
    while (!this->button->isPressed())
    {
    }
    unsigned long start = millis();
    unsigned long startTemp;
    bool fixFlag = false;
    while (millis() - start < N3)
    {
        float temperature = this->tmp->detect();
        this->l2->blink(250);
        int progressPerc = map((N3 - (millis() - start)), 0, 10000, 0, 100);
        this->lcd->printBar(progressPerc);
        Serial.println("temp" + String(temperature));
        startTemp = millis();
        do
        {
            if (millis() - startTemp > N4)
            {
                Serial.println("warning");
                this->lcd->showMessage("Detected a problem");
                while (!fixFlag)
                {
                    /* If there is something available in the serial line */
                    if (Serial.available() == 1)
                    {
                        String answer = Serial.readStringUntil('\n');
                        if (answer == "fix")
                        {
                            fixFlag = true;
                        }
                    }
                }
                start = millis();
                fixFlag = false;
                break;
            }
        } while (temperature > MAXTEMP);
    }
    this->lcd->showMessage("Washing complete you can leave!");
    startWashing = false;
    washingFinished = true;
    this->setActive(false);
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