#include <Arduino.h>
#include "../lib/Sonar.hpp"

Sonar::Sonar(int echo, int trig) {
    this->echo = echo;
    this->trig = trig;
    pinMode(this->trig, OUTPUT);
    pinMode(this->echo, INPUT);
}

float Sonar::getDistance() {
    digitalWrite(this->trig,LOW);
    delayMicroseconds(3);
    digitalWrite(this->trig,HIGH);
    delayMicroseconds(5);
    digitalWrite(this->trig,LOW);

    float receive = pulseIn(this->echo, HIGH);
    float time = receive / 1000.0 / 1000.0 / 2.0;
    return time * this->vs;
}