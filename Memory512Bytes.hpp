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
    string memData = "0"; //"00000000000000000000000000000000";

public:
    Memory512Bytes()
    {
        this->memory = new char *[128];
        for (int i = 0; i < 128; i++)
        {
            this->memory[i] = new char[32];
        }
        // this->memData 

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
                // cout << "INT ADDRESS: " << intAddress << endl;
               // cout << "Entrou no laco para enfiar na mem" << endl;
                for (int i = 0; i < 32; i++)
                {
                    cout << "I: " << i << endl;
                    if (memRead)
                    {
                        cout << "Entra no if" << endl;
                        cout << "MEM DATA SIZE " << memData.size() << endl;
                        cout << "MemData " << memData << endl;
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

    void imprimirMemoria()
    {
        for(int i = 0; i < 128; i++)
        {
            cout << " \n";
            for(int j = 0; j < 32;j++)
            {
                cout << memory[i][j];
            }
        }
    }
};

#endif