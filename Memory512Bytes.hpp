#ifndef MEMORY_512_BYTES_HPP
#define MEMORY_512_BYTES_HPP
#include <iostream>
#include <string>

using namespace std;

class Memory512Bytes
{
private:
    const string ZERO = "00000000000000000000000000000000";
    char **memory;
    string memData;

public:
    Memory512Bytes()
    {
        this->memory = new char *[128];
        for (int i = 0; i < 128; i++)
        {
            this->memory[i] = new char[32];
        }
        this->memData = ZERO;
    };
    ~Memory512Bytes()
    {
        for (int i = 0; i < 128; i++)
        {
            delete[] memory[i];
        }
        delete[] memory;
    };
    void makeOperation(string address, string writeData, bool memRead, bool memWrite)
    {
        if (memRead || memWrite)
        {
            int intAddress = stoi(address, 0, 2);
            if (intAddress > 128)
            {
                cout << "This address don't exist!" << endl;
                exit(1);
            }
            else
            {
                for (int i = 0; i < 32; i++)
                {
                    if (memRead)
                    {
                        memData[i] = this->memory[intAddress][i];
                    }
                    else
                    {
                        this->memory[intAddress][i] = writeData[i];
                    }
                }
            }
        }
    };
    string getMemData(){
        return memData;
    }
};

#endif