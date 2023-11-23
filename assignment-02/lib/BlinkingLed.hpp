#ifndef __BLININGLED__
#define __BLINKINGLED__

#include "Led.hpp"

class BlinkingLed : public Led {

public:
    BlinkingLed(int pin);
    void blink(int blinkTime);

private:
    Led *led;

};

#endif