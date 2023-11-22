#include <Arduino.h>
#include "../lib/Scheduler.hpp"
#include "../lib/BlinkTask.hpp"
#include "../lib/PirDetectionTask.hpp"
#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"
#include "../lib/ProceedTask.hpp"
#include "../lib/PreWashingTask.hpp"

Scheduler sched;
bool carDetected = false;
bool blinkStart = false;
bool carEntered = false;

void setup()
{
    Serial.begin(9600);
    sched.init(100);

    Task *pirDetectionTask = new PirDetectionTask(PIR_PIN);
    pirDetectionTask->init(PIR_PERIOD);
    sched.addTask(pirDetectionTask);

    pirDetectionTask->setActive(true);

    Task *blinkTaskExtern = new BlinkTask();
    blinkTaskExtern->init(BLINK_PERIOD_START);
    sched.addTask(blinkTaskExtern);

    Task *welcomeTask = new WelcomeTask(nullptr);
    welcomeTask->init();
    sched.addTask(welcomeTask);

    Task *preWashingTask = new PreWashingTask();
    preWashingTask->init();
    sched.addTask(preWashingTask);

    Task *proceedTask = new ProceedTask();
    proceedTask->init();
    sched.addTask(proceedTask);
}

void loop()
{
    Serial.println("Sto schedulando");
    sched.schedule();
}
