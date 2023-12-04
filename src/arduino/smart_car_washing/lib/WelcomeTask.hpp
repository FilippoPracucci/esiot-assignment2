#ifndef __WELCOMETASK__
#define __WELCOMETASK__

#include "Task.hpp"
#include "Led.hpp"
#include "Gate.hpp"
#include "Lcd.hpp"

class WelcomeTask : public Task
{

public:
    WelcomeTask();
    void init(int period);
    void tick();
    bool isActive() override;

private:
    enum
    {
        START,
        WAITING,
        END
    } state;
    Led *l1;
    String welcomeMessage;
    Lcd *lcd;
    Gate *gate;
    bool sendUpdate;
};

#endif