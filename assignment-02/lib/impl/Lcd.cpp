#include <Arduino.h>
#include "../api/Lcd.hpp"

Lcd::Lcd(int address, int cols, int rows) {
    this->lcd = LiquidCrystal_I2C(address, cols, rows);
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