#ifndef __WASHINGTASK__
#define __WASHINGTASK__

#include "Task.hpp"
#include "Button.hpp"
#include "BlinkingLed.hpp"
#include "Lcd.hpp"
#include "Tmp.hpp"

class WashingTask : public Task
{

public:
    WashingTask();
    void init();
    void tick();
    bool isActive() override;
    bool sendWarning;
    bool fixFlag;

private:
    enum {WAITING_BUTTON, WASHING, ERROR, END} state;
    signed long startTemp;
    Button *button;
    Lcd *lcd;
    BlinkingLed *l2;
    Tmp *tmp;
    bool changeMsg = true;
};

#endif