#include <Arduino.h>
#include "../lib/Button.hpp"

Button::Button(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

bool Button::isPressed() {
    /* bool already_pressed = false;
    while (true) {
        int buttonState = digitalRead(this->pin);
        if (buttonState == HIGH && !already_pressed) {
            already_pressed = true;   
            delay(100);
        } else {
            already_pressed = false;
        }
    } */
    return (digitalRead(this->pin) == HIGH);
}
