#include <Arduino.h>
#include "../lib/Button.hpp"

Button::Button(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

bool Button::isPressed() {
    return (digitalRead(this->pin) == HIGH);
}
