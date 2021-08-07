#ifndef REGISTRADORES_HPP
#define REGISTRADORES_HPP

#include <iostream>
#include <string>

using namespace std;

class Registradores
{
    private:
        string* registrador;
        int n = 32; //Número de bits em um registrador

        void preenche(){for(int i = 0; i < n; i++) this->registrador[i] = '0';};
    public:
        Registradores(){this->registrador = new string[n];};
        ~Registradores(){};

        string* getRegistrador(){return this->registrador;};
};

#endif // REGISTRADORES_HPP