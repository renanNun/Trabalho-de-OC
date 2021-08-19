#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

#include <iostream>

using namespace std;

class PC 
{
    public:
        static PC& getInstance()
        {
            static PC instance;

            return instance;
        }
    private:
        PC(){};
        ~PC(){
            resetValue();
        };

        PC(PC const&);
        void operator=(PC const&);

        int value;
    public:
        void resetValue(){value = 0;};
        int getPC(){return this->value;};
        void incremetPC(){this->value = this->value + 4;};
};

#endif // PROGRAMCOUNTER_H