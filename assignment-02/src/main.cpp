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
bool blinkStart = false;
bool carEntered = false;
bool startWashing = false;
bool washingFinished = false;

void setup()
{
    Serial.begin(9600);
    sched.init(100);
    startDetecting = true;

    Task *pirDetectionTask = new PirDetectionTask(PIR_PIN);
    pirDetectionTask->init(PIR_PERIOD);
    sched.addTask(pirDetectionTask);

    pirDetectionTask->setActive(true);

    Task *welcomeTask = new WelcomeTask(nullptr);
    welcomeTask->init();
    sched.addTask(welcomeTask);

    Task *preWashingTask = new PreWashingTask();
    preWashingTask->init();
    sched.addTask(preWashingTask);

    Task *proceedTask = new ProceedTask();
    proceedTask->init();
    sched.addTask(proceedTask);

    Task *washingTask = new WashingTask();
    washingTask->init();
    sched.addTask(washingTask);

    Task *exitTask = new ExitTask();
    exitTask->init();
    sched.addTask(exitTask);
}

void loop()
{
    /* //Serial.println("Sto schedulando");
    //Serial.println("START DETECTING = " + String(startDetecting));
    //Serial.println("CAR DETECTED = " + String(carDetected));
    //Serial.println("BLINK START = " + String(blinkStart));
    //Serial.println("CAR ENTERED = " + String(carEntered));
    //Serial.println("START WASHING = " + String(startWashing));
    //Serial.println("WASHING FINISHED = " + String(washingFinished));
    //Serial.println("\n\n\n\n\n"); */
    sched.schedule();
}
