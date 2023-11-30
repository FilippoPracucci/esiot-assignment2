#include <Arduino.h>
#include "../lib/Scheduler.hpp"
#include "../lib/PirDetectionTask.hpp"
#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"
#include "../lib/ProceedTask.hpp"
#include "../lib/PreWashingTask.hpp"
#include "../lib/WashingTask.hpp"
#include "../lib/ExitTask.hpp"

Scheduler sched;
bool startDetecting;
bool carDetected = false;
bool canProceed = false;
bool carEntered = false;
bool startWashing = false;
bool washingFinished = false;
int completedWashing = 0;

void setup()
{
    Serial.begin(9600);
    sched.init(100);
    startDetecting = true;

    Task *pirDetectionTask = new PirDetectionTask(PIR_PIN);
    pirDetectionTask->init(PIR_PERIOD);
    sched.addTask(pirDetectionTask);

    Task *welcomeTask = new WelcomeTask();
    welcomeTask->init();
    sched.addTask(welcomeTask);

    Task *proceedTask = new ProceedTask();
    proceedTask->init();
    sched.addTask(proceedTask);

    Task *preWashingTask = new PreWashingTask();
    preWashingTask->init();
    sched.addTask(preWashingTask);

    Task *washingTask = new WashingTask();
    washingTask->init();
    sched.addTask(washingTask);

    Task *exitTask = new ExitTask();
    exitTask->init();
    sched.addTask(exitTask);
    Serial.println("Fine setup " + String(completedWashing));
}

void loop()
{
    sched.schedule();
}
