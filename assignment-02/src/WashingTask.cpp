#include "../lib/WashingTask.hpp"
#include "../lib/config.h"

extern bool startWashing;
extern bool washingFinished;

WashingTask::WashingTask() {

}

void WashingTask::init() {
    Serial.println("Init washing");
    this->button = new Button(BUTTON_PIN);
    this->lcd = new Lcd(0x27, LCD_COLS, LCD_ROWS);
    this->l2 = new BlinkingLed(L2);
    this->tmp = new Tmp(TMP_PIN);
}

void WashingTask::tick() {
    Serial.println("Sono il tick di washing");
    while (!this->button->isPressed()) {}
    unsigned long start = millis();
    while (millis() - start < N3) {
        this->l2->blink(250);
        this->lcd->showMessage(String((N3 - (millis() - start)) / 1000));
        Serial.println("Temperatura = " + String(tmp->detect()));
    }
    this->lcd->showMessage("Washing complete you can leave!");
    startWashing = false;
    washingFinished = true;
    Serial.println("Fine tick washing");
    this->setActive(false);
}

bool WashingTask::isActive() {
    if (startWashing) {
        this->setActive(true);
        return true;
    }
    return false;
}