#include <Arduino.h>
#include "../lib/Gate.hpp"

Gate::Gate(int pin) {
    this->servo.attach(pin);
}

void Gate::open() {
    this->servo.write(OPEN_ANGLE);
    delay(50);
}

void Gate::close() {
    this->servo.write(CLOSE_ANGLE);
    delay(50);
}
