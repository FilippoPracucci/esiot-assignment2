#ifndef __WASHINGTASK__
#define __WASHINGTASK__

#include "Task.hpp"
#include "Button.hpp"
#include "BlinkingLed.hpp"
#include "Lcd.hpp"
#include "Tmp.hpp"
#include "MsgService.h"

class WashingTask : public Task {

public:
    WashingTask();
    void init();
    void tick();
    bool isActive() override;

private:
    Button *button;
    Lcd *lcd;
    BlinkingLed *l2;
    Tmp *tmp;
    
};

#endif