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
}

void WashingTask::tick() {
    Serial.println("Sono il tick di washing");
    while (!this->button->isPressed()) {
        Serial.println("Aspetto il bottone");
    }
    unsigned long start = millis();
    while (millis() - start < N3) {
        this->l2->blink(250);
        this->lcd->showMessage(String((N3 - (millis() - start)) / 1000));
    }
    this->lcd->showMessage("Washing complete you can leave!");
    startWashing = false;
    washingFinished = true;
    Serial.println("Fine tick washing");
}

bool WashingTask::isActive() {
    if (startWashing) {
        this->setActive(true);
        return true;
    }
    return false;
}