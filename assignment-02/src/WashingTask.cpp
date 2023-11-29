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
    // Serial.println("Init washing");
    this->button = new Button(BUTTON_PIN);
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->l2 = new BlinkingLed(L2);
    this->tmp = new Tmp(TMP_PIN);
}

void WashingTask::tick()
{
    Serial.println("washing routine");
    // Serial.println("Sono il tick di washing");
    while (!this->button->isPressed())
    {
    }
    unsigned long start = millis();
    unsigned long startTemp;
    bool flag = false;
    while (millis() - start < N3)
    {
        float temperature = this->tmp->detect();
        this->l2->blink(250);
        this->lcd->showMessage(String((N3 - (millis() - start)) / 1000));
        // Serial.println("Temperatura = " + String(tmp->detect()));
        Serial.println("temp" + String(temperature));
        startTemp = millis();
        do
        {
            if (millis() - startTemp > N4)
            {
                Serial.println("warning");
                while (!flag)
                {
                    /* If there is something available in the serial line */
                    if (Serial.available() == 1)
                    {
                        String answer = Serial.readStringUntil('\n');
                        if (answer == "fix")
                        {
                            flag = true;
                        }
                    }
                }
                start = millis();
                flag = false;
                break;
            }
        } while (temperature > MAXTEMP);
    }
    this->lcd->showMessage("Washing complete you can leave!");
    startWashing = false;
    washingFinished = true;
    // Serial.println("Fine tick washing");
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