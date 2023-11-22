#ifndef __PREWASHINGTASK__
#define __PREWASHINGTASK__

#include "Task.hpp"
#include "Led.hpp"
#include "Gate.hpp"
#include "Lcd.hpp"

class PreWashingTask : public Task {

public:
    PreWashingTask();
    void init();
    void tick();
    bool isActive() override;

private:
    Gate* gate;
    Led* l2;
    Lcd* lcd;
    String readyMessage;
};

#endif