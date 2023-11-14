#include <Arduino.h>
#include "../api/Gate.hpp"

Gate::Gate(int pin) {
    this->servo.attach(pin);
}

void Gate::open() {
    this->servo.write(OPEN_ANGLE);
}

void Gate::close() {
    this->servo.write(CLOSE_ANGLE);
}
