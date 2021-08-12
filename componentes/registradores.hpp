#ifndef REGISTRADORES_HPP
#define REGISTRADORES_HPP

#include <iostream>
#include <string>

using namespace std;

class Registradores
{
    private:
        string** registradores;
        int n = 32; //Número de bits em um registrador

        string data1;
        string data2;

        int regW;
        int controlRegW;

    public:
        Registradores();
        ~Registradores();
        

        void busca(int i, int j, int write, int controlData);
        void writeBack(string* dataW);
        
        static string** getRegistradores(){return this->registradores;};
        string getSaida1(){return this->data1;};
        string getSaida2(){return this->data2;};
        string mapeia(string reg);
};

#endif // REGISTRADORES_HPP