#include <Arduino.h>
#include "../lib/Lcd.hpp"

Lcd::Lcd(int address, int cols, int rows) : lcd(address, cols, rows) {
    this->lcd.init();
    this->lcd.backlight();
}

void Lcd::showMessage(String message) {
    this->clear();
    this->lcd.print(message);
}

void Lcd::clear() {
    this->lcd.clear();
}