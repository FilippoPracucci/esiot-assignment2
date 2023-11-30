#ifndef __EXITTASK__
#define __EXITTASK__

#include "Task.hpp"
#include "Led.hpp"
#include "Gate.hpp"
#include "Sonar.hpp"

class ExitTask : public Task
{

public:
    ExitTask();
    void init();
    void tick();
    bool isActive() override;

private:
    Led *l2;
    Led *l3;
    Gate *gate;
    Sonar *sonar;
};

#endif