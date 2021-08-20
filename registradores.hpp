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

        string* data1;
        string* data2;

        int regW;
        int controlRegW;

    public:
        Registradores();
        ~Registradores();


        void busca(int i, int j, int write, int controlData);
        void writeBack(string* dataW);

        void escreve(int pos,string aux)
        {
            for(int i = 0; i < 32; i++) registradores[pos][i] = aux[i];
        };

        string getReg(int pos)
        {
            string line = "";

            for(int i = 0; i < 32; i++) line += registradores[pos][i];
            return line;
        };

        void imprime()
        {
            for(int i = 0; i < 32; i++){
                cout << "\n\t";
                for(int j = 0; j < 32;j++)
                    cout << registradores[i][j];
            }
        };
        
        string** getRegistradores(){return registradores;};
        string* getSaida1(){return this->data1;};
        string* getSaida2(){return this->data2;};
        string mapeia(string reg);
};

#endif // REGISTRADORES_HPP