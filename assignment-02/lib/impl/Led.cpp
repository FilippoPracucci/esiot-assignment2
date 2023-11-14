#include <Arduino.h>
#include "../api/led.hpp"

Led::Led(int pin) {
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}

void Led::switchOn() {
    digitalWrite(this->pin, HIGH);
}

void Led::switchOff() {
    digitalWrite(this->pin, LOW);
}
