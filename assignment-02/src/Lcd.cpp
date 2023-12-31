#include <Arduino.h>
#include "../lib/Lcd.hpp"

byte blackSquare[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111};

Lcd::Lcd(int address, int cols, int rows) : lcd(address, cols, rows)
{
    this->lcd.init();
    this->lcd.backlight();
    this->rows = rows;
    this->cols = cols;
    this->lcd.createChar(0, blackSquare);
}

void Lcd::showMessage(String message)
{
    this->clear();
    /* Print in two lines if the message is too long for a single line. */
    if (message.length() > this->cols)
    {
        this->lcd.print(message.substring(0, this->cols));
        this->lcd.setCursor(0, 1);
        this->lcd.print(message.substring(this->cols, message.length()));
    }
    else
    {
        this->lcd.print(message);
    }
}

void Lcd::clear()
{
    this->lcd.clear();
}

void Lcd::printBar(int perc)
{
    this->lcd.clear();
    int barToDraw = map(perc, 0, 100, 0, 32);
    this->lcd.setCursor(0, 0);
    for (int i = 0; i < barToDraw; i++)
    {
        if (i == 15)
        {
            lcd.setCursor(0, 1);
        }
        this->lcd.write(byte(0));
    }
}