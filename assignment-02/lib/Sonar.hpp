#ifndef __SONAR__
#define __SONAR__

#define TEMP 20

class Sonar
{
public:
    Sonar(int echo, int trig);
    float getDistance();

private:
    const float vs = 331.45 + 0.62*TEMP;
    int echo;
    int trig;
    
};

#endif