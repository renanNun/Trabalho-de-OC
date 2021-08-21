#ifndef MEMORY_512_BYTES_HPP
#define MEMORY_512_BYTES_HPP
#include <iostream>
#include <string>
#include "Log.hpp"

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

        for(int i = 0; i < 128; i++)
        {
            for(int j = 0; j < 32;j++)
            {
                memory[i][j] = '0';
            }
        }
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
                //cout << "INT ADDRESS: " << intAddress << endl;
                //cout << "\n" << memory[intAddress][0] << endl;
                for (int i = 0; i < 32; i++)
                {
                    //cout << "I: " << i << endl;
                    if (memRead)
                    {
                        //cout << "Entra no if" << endl;
                        //cout << "MEM DATA SIZE " << this->memData.size() << endl;
                        //cout << "MemData " << this->memData << endl;
                        this->memData[i] = this->memory[intAddress][i];
                    }
                    else
                    {
                        this->memory[intAddress][i] = writeData[i];
                    }
                }
            }
        }
    };

    void imprimirMemoria()
    {
        string line = "";
        
        for(int i = 0; i < 128; i++)
        {
            line = "";
            for(int j = 0; j < 32;j++)
            {
                line += memory[i][j];
            }
            Log::getInstance().line(line);
        }
    };

    string getMemData(){
        return memData;
    };
};

#endif // MEMORY_512_BYTES_HPP