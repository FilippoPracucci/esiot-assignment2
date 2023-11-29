#include <Arduino.h>
#include "../lib/Pir.hpp"

Pir::Pir(int pin) {
    this->pin = pin;
    pinMode(this->pin, INPUT);
}

bool Pir::detect() {
    if (digitalRead(this->pin) == HIGH) {
        long t = millis();
        while (millis() - t < 1500) {
            if (digitalRead(this->pin) == HIGH) {
                //Serial.println("Detected");
                return true;
            }
        }
        /* //Serial.println("Detected");
        return true; */
    }
    //Serial.println("Not detected");
    return false;
    /* return analogRead(this->pin) >= 250; */
}
