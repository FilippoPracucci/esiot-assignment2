#ifndef __GATE__
#define __GATE__

class Gate {
    public:
        Gate(int pin);
        void open();
        void close();
    private:
        int pin;
};

#endif