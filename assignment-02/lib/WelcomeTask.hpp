#ifndef __WELCOMETASK__
#define __WELCOMETASK__

#include "Task.hpp"
#include "Led.hpp"
#include "Gate.hpp"
#include "Lcd.hpp"

class WelcomeTask : public Task {

public:
    WelcomeTask(Task* blinkTask);
    void init();
    void tick();
    bool isActive() override;

private:
    Led* l1;
    String welcomeMessage;
    Lcd* lcd;
    Gate* gate;
    Task* blinkTask;
};

#endif