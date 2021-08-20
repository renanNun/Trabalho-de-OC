#ifndef PROGRAMCOUNTER_H
#define PROGRAMCOUNTER_H

#include <iostream>
#include<math.h>

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

        int convertBin(string address)
        {
            int dec = 0;
            int bin = stoi(address);
            for(int i = 0; i < bin ;i++)
            {
                dec = dec + pow(2,i) * (bin % 10);
                bin = bin/10;
            }

            return bin;
        }

        void getJump(string address)
        {
            int convert = convertBin(address);

            value = value + (4 * convert);
        };
    public:
        void resetValue(){value = 0;};
        int getPC(){return this->value;};
        void incremetPC(){this->value = this->value + 4;};
        void setPC(string _value){int value = convertBin(_value); this->value = value;};
};

#endif // PROGRAMCOUNTER_H