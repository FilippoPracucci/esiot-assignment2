#include <Arduino.h>
#include "../lib/Gate.hpp"

Gate::Gate(int pin)
{
    this->pin = pin;
}

void Gate::open()
{
    this->servo.write(OPEN_ANGLE);
    delay(1000);
}

void Gate::close()
{
    this->servo.write(CLOSE_ANGLE);
    delay(1000);
}

void Gate::on()
{
    this->servo.attach(this->pin);
}

void Gate::off()
{
    this->servo.detach();
}
