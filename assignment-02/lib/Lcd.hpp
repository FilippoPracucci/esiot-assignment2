#ifndef __LCD__
#define __LCD__

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class Lcd
{

public:
    Lcd(int address, int cols, int rows);
    void showMessage(String message);
    void printBar(int perc);
    void clear();

private:
    LiquidCrystal_I2C lcd;
    int rows;
    int cols;
};

#endif