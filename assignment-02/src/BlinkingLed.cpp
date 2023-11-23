#include <Arduino.h>
#include "../lib/BlinkingLed.hpp"

BlinkingLed::BlinkingLed(int pin) : Led(pin) {
    this->led = new Led(pin);
}

void BlinkingLed::blink(int blinkTime) {
    this->led->switchOn();
    delay(blinkTime);
    this->led->switchOff();
    delay(blinkTime); //this can be unnecessary
}
