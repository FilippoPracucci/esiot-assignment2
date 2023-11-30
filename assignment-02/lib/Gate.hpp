#ifndef __GATE__
#define __GATE__

#include <ServoTimer2.h>

#define OPEN_ANGLE 750
#define CLOSE_ANGLE 2250

class Gate
{

public:
    Gate(int pin);
    void open();
    void close();
    void on();
    void off();

private:
    ServoTimer2 servo;
    int pin;
};

#endif