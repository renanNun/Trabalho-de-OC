#ifndef REGISTRADORES_HPP
#define REGISTRADORES_HPP

#include <iostream>
#include <string>

using namespace std;

class Registradores
{
private:
    string **registradores;
    int n = 32; //Número de bits em um registrador

    string *data1;
    string *data2;

    int regW;
    int controlRegW;

public:
    Registradores();
    ~Registradores();

    void busca(int i, int j, int write, int controlData);
    void writeBack(string *dataW);

    void escreve(int pos, string aux)
    {

        for (int i = 0; i < 32; i++)
        {
            registradores[pos][i] = aux[i];
        }
    };

    string getReg(int pos)
    {
        string line = "";

        for (int i = 0; i < 32; i++)
            line += registradores[pos][i];
        return line;
    };

void imprime()
    {
        for (int i = 0; i < 32; i++)
        {

            cout << "\n\t";
            switch (i)
            {
            case 0:
                cout << "$zero: ";
                break;
            case 1:
                cout << "$at: ";
                break;
            case 2:
                cout << "$v0: ";
                break;
            case 3:
                cout << "$v1: ";
                break;
            case 4:
                cout << "$a0: ";
                break;
            case 5:
                cout << "$a1: ";
                break;
            case 6:
                cout << "$a2: ";
                break;
            case 7:
                cout << "$a3: ";
                break;
            case 8:
                cout << "$t0: ";
                break;
            case 9:
                cout << "$t1: ";
                break;
            case 10:
                cout << "$t2: ";
                break;
            case 11:
                cout << "$t3: ";
                break;
            case 12:
                cout << "$t4: ";
                break;
            case 13:
                cout << "$t5: ";
                break;
            case 14:
                cout << "$t6: ";
                break;
            case 15:
                cout << "$t7: ";
                break;
            case 16:
                cout << "$s0: ";
                break;
            case 17:
                cout << "$s1: ";
                break;
            case 18:
                cout << "$s2: ";
                break;
            case 19:
                cout << "$s3: ";
                break;
            case 20:
                cout << "$s4: ";
                break;
            case 21:
                cout << "$s5: ";
                break;
            case 22:
                cout << "$s6: ";
                break;
            case 23:
                cout << "$s7: ";
                break;
            case 24:
                cout << "$t8: ";
                break;
            case 25:
                cout << "$t9: ";
                break;
            case 26:
                cout << "$k0: ";
                break;
            case 27:
                cout << "$k1: ";
                break;
            case 28:
                cout << "$gp: ";
                break;
            case 29:
                cout << "$sp: ";
                break;
            case 30:
                cout << "$fp: ";
                break;
            case 31:
                cout << "$ra: ";
                break;

            default:
                break;
            }
            for (int j = 0; j < 32; j++)
                cout << registradores[i][j];
        }
    };

    string **getRegistradores() { return registradores; };
    string *getSaida1() { return this->data1; };
    string *getSaida2() { return this->data2; };
    string mapeia(string reg);
};

#endif // REGISTRADORES_HPP