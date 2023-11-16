#ifndef __GATE__
#define __GATE__

#include <Servo.h>

#define OPEN_ANGLE 90
#define CLOSE_ANGLE 0

class Gate {

public:
    Gate(int pin);
    void open();
    void close();

private:
    Servo servo;

};

#endif