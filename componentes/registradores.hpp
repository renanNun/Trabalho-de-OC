#ifndef REGISTRADORES_HPP
#define REGISTRADORES_HPP

#include <iostream>
#include <string>

using namespace std;

class Registradores
{
    private:
        int** registradores;
        int n = 32; //Número de bits em um registrador

        int data1;
        int data2;

        int regW;
        int controlRegW;

    public:
        Registradores();
        ~Registradores();

        void busca(int i, int j, int write, int controlData);
        void writeBack(int* dataW);
        
        static int* getRegistradores(){return this->registradores;};
        int getSaida1(){return this->data1;};
        int getSaida2(){return this->data2;};
};

#endif // REGISTRADORES_HPP