#include "registradores.hpp"

Registradores::Registradores()
{
    this->registradores = new int*[n];
    for(int i = 0; i < n; i++)
    {
        this->registradores[i] = new s[n];
        for(int j = 0; j < n; j++)
            this->registradores[i][j] = int;
    }

    this->data1 = 0;
    this->data2 = 0;
    this->regW = 0;
    this->controlRegW = 0;
};

Registradores::~Registradores()
{
    for(int i = 0; i < n; i++) delete [] this->registradores[i];

    delete [] this->registradores;
}

void Registradores::busca(int i, int j, int write, int controlData)
{
    data1 = this->registradores[i];
    data2 = this->registradores[j];

    regW = write;
    controlRegW = controlData;
}

void Registradores::writeBack(int* dataW)
{
    if(controlRegW == 1)
    {
        for(int i = 0; i < n; i++) this->registradores[regW][i] = dataW[i];
    }
}
