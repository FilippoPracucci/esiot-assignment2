#include <Arduino.h>
#include "../api/Tmp.hpp"

Tmp::Tmp(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

float Tmp::detect() {
    return ((analogRead(this->pin) * 0.00488) - 0.5) / 0.01;
}
