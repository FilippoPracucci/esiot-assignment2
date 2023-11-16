#ifndef __BLININGLED__
#define __BLINKINGLED__

#include "Led.hpp"

class BlinkingLed : public Led {

public:
    void blink(int blinkTime);

};

#endif