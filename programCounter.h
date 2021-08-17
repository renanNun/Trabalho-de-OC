#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

#include <iostream>

using namespace std;

class PC 
{
    private:
        int value = 0;
    public:
        PC(){};
        ~PC(){};

        int getPC(){return this->value;};
        void incremetPC(){this->value = this->value + 4;};
};

#endif // PROGRAMCOUNTER_H