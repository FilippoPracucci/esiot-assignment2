#include "Scheduler.hpp"
#include <TimerOne.h>

volatile bool timerFlag;

void timerHandler() {
    timerFlag = true;
}

void Scheduler::init(int p) {
    this->generalPeriod = p;
    timerFlag = false;
    long period = 1000l * this->generalPeriod;
    Timer1.initialize(period);
    Timer1.attachInterrupt(timerHandler);
    this->taskList = LinkedList<Task*>();
}

void Scheduler::addTask(Task* task) {
    this->taskList.add(task);
}

void Scheduler::schedule() {
    while (!timerFlag) {}
    timerFlag = false;

    for (int i = 0; i < this->taskList.size(); i++) {
        if (this->taskList.get(i)->isActive() && this->taskList.get(i)->updateAndCheckTime(this->generalPeriod)) {
            this->taskList.get(i)->tick();
        }
    }
}
