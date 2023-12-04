#include <Arduino.h>
#include "../lib/Scheduler.hpp"
#include "../lib/PirDetectionTask.hpp"
#include "../lib/WelcomeTask.hpp"
#include "../lib/config.h"
#include "../lib/ProceedTask.hpp"
#include "../lib/PreWashingTask.hpp"
#include "../lib/WashingTask.hpp"
#include "../lib/ExitTask.hpp"
#include "../lib/BlinkTask.hpp"

Scheduler sched;
bool startDetecting;
bool carDetected = false;
bool canProceed = false;
bool carEntered = false;
bool startWashing = false;
bool washingFinished = false;
bool blinkStart500 = false;
bool blinkStart100 = false;
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
    welcomeTask->init(WELCOME_PERIOD);
    sched.addTask(welcomeTask);

    Task *proceedTask = new ProceedTask();
    proceedTask->init(PROCEED_PERIOD);
    sched.addTask(proceedTask);

    Task *preWashingTask = new PreWashingTask();
    preWashingTask->init();
    sched.addTask(preWashingTask);

    Task *washingTask = new WashingTask();
    washingTask->init(WASHING_PERIOD);
    sched.addTask(washingTask);

    Task *exitTask = new ExitTask(); 
    exitTask->init(EXIT_PERIOD);
    sched.addTask(exitTask);
    Serial.println("Fine setup " + String(completedWashing));

    Task *blinkTask500 = new BlinkTask();
    blinkTask500->init(1000);
    sched.addTask(blinkTask500);

    Task *blinkTask100 = new BlinkTask();
    blinkTask100->init(100);
    sched.addTask(blinkTask100);

}

void loop()
{
    sched.schedule();
}
