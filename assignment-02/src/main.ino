#include <Arduino.h>
#include "../lib/Scheduler.hpp"
#include "../lib/BlinkTask.hpp"
#include "../lib/PirDetectionTask.hpp"
#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"

Scheduler sched;
bool carDetected = false;

void setup() {
    Serial.begin(9600);
    sched.init(100);

    Task* pirDetectionTask = new PirDetectionTask(PIR_PIN);
    pirDetectionTask->init(PIR_PERIOD);
    sched.addTask(pirDetectionTask);

    pirDetectionTask->setActive(true);

    Task* welcomeTask = new WelcomeTask();
    welcomeTask->init(500);
    sched.addTask(welcomeTask);
}

void loop() {
    sched.schedule();
}
