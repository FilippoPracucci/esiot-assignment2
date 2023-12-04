#ifndef __PROCEEDTASK__
#define __PROCEEDTASK__

#include "Lcd.hpp"
#include "Sonar.hpp"
#include "Task.hpp"
#include "Led.hpp"
class ProceedTask : public Task
{
public:
    ProceedTask();
    void init(int period);
    void tick();
    bool isActive() override;

private:
    enum {MONITORING, END} state;
    long monitoringTimer;
    Lcd *lcd;
    Sonar *sonar;
    String proceedMessage;
    Led *l2;
    bool changeMsg = true;
};

#endif