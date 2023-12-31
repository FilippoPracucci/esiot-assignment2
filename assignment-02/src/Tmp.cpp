#include <Arduino.h>
#include "../lib/Tmp.hpp"

Tmp::Tmp(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

float Tmp::detect() {
    return ((analogRead(this->pin) * 0.00488) - 0.5) / 0.01;
    /* return ((analogRead(this->pin) * 0.0032) - 0.5) / 0.01; */
}
