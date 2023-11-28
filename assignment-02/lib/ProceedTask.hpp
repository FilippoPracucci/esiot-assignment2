#ifndef __PROCEEDTASK__
#define __PROCEEDTASK__

#include "Lcd.hpp"
#include "Sonar.hpp"
#include "Task.hpp"
#include "BlinkingLed.hpp"

class ProceedTask : public Task {
public:
    ProceedTask();
    void init();
    void tick();
    bool isActive() override;

private:
    Lcd* lcd;
    Sonar* sonar;
    String proceedMessage;
    BlinkingLed *l2;

};

#endif