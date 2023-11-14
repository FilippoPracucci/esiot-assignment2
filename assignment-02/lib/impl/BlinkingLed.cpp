#include <Arduino.h>
#include "../api/BlinkingLed.hpp"

void BlinkingLed::blink(int blinkTime) {
    this->switchOn();
    delay(blinkTime);
    this->switchOff();
    delay(blinkTime); //this can be unnecessary
}
