#include <Arduino.h>
#include "../api/Pir.hpp"

Pir::Pir(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

bool Pir::detect() {
    return digitalRead(this->pin) == HIGH;
}
