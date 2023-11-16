#include <Arduino.h>
#include "../lib/BlinkingLed.hpp"

void BlinkingLed::blink(int blinkTime) {
    this->switchOn();
    delay(blinkTime);
    this->switchOff();
    delay(blinkTime); //this can be unnecessary
}
