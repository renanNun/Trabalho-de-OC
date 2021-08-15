#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

#include <iostream>

using namespace std;

class PC 
{
    private:
        int value;
    public:
        PC(){
            this->value = 0;
        };
        ~PC(){};

        int getPC(){return this->value;};
        void incremetPC(){this->value = this->value + 1;};
};

#endif // PROGRAMCOUNTER_H