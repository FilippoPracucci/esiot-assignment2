#include <Arduino.h>
#include "../lib/Pir.hpp"

//#define PIR_ON
#define PHOTO_ON
#define PIN_ORA 2
Pir::Pir(int pin) {
    this->pin = pin;
    pinMode(2, INPUT);
}

bool Pir::detect() {
    #ifdef PIR_ON
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
    #endif
    #ifdef PHOTO_ON
    bool flag = digitalRead(PIN_ORA);
    Serial.println(flag);
    if (flag) {
        Serial.println("HIGH");
        return true;
    } else {
        Serial.println("LOW");
        return false;
    }
    //return !(digitalRead(2) == LOW);
    #endif
    /* return analogRead(this->pin) >= 250; */
}
