#include <Arduino.h>
#include "../lib/Scheduler.hpp"
#include "../lib/BlinkTask.hpp"

Scheduler sched;

void setup() {
    Serial.begin(9600);
    sched.init(100);

    Task* blinkTask = new BlinkTask(7);
    blinkTask->init(100);

    Task* blinkTask2 = new BlinkTask(8);
    blinkTask2->init(200);

    sched.addTask(blinkTask);
    sched.addTask(blinkTask2);
}

void loop() {
    sched.schedule();
}
