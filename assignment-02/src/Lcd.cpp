#include <Arduino.h>
#include "../lib/Lcd.hpp"

Lcd::Lcd(int address, int cols, int rows) : lcd(address, cols, rows) {
    this->lcd.init();
    this->lcd.backlight();
    this->rows = rows;
    this->cols = cols;
}

void Lcd::showMessage(String message) {
    this->clear();
    /* Print in two lines if the message is too long for a single line. */
    if (message.length() > this->cols) {
        this->lcd.print(message.substring(0, this->cols));
        this->lcd.setCursor(0, 1);
        this->lcd.print(message.substring(this->cols, message.length()));
    } else {
        this->lcd.print(message);
    }
}

void Lcd::clear() {
    this->lcd.clear();
}