#ifndef REGISTRADORES_HPP
#define REGISTRADORES_HPP

#include <iostream>
#include <string>

#include "Log.hpp"

using namespace std;

class Registrador
{
private:
    string **registradores;
    int n = 32; //Número de bits em um registrador

    string *data1;
    string *data2;

    int regW;
    int controlRegW;

public:
    Registrador();
    ~Registrador();

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
        string line = "";
        Log::getInstance().line("Imprimindo Registradores: ");
        for (int i = 0; i < 32; i++)
        {
            line = "";
            line += "\t";
            switch (i)
            {
            case 0:
                line += "$zero: ";
                break;
            case 1:
                line += "$at: ";
                break;
            case 2:

                line += "$v0: ";

                break;
            case 3:
                line += "$v1: ";
                break;
            case 4:
                line += "$a0: ";
                break;
            case 5:
                line += "$a1: ";
                break;
            case 6:
                line += "$a2: ";
                break;
            case 7:
                line += "$a3: ";
                break;
            case 8:
                line += "$t0: ";
                break;
            case 9:
                line += "$t1: ";
                break;
            case 10:
                line += "$t2: ";
                break;
            case 11:
                line += "$t3: ";
                break;
            case 12:
                line += "$t4: ";
                break;
            case 13:
                line += "$t5: ";
                break;
            case 14:
                line += "$t6: ";
                break;
            case 15:
                line += "$t7: ";
                break;
            case 16:
                line += "$s0: ";
                break;
            case 17:
                line += "$s1: ";
                break;
            case 18:
                line += "$s2: ";
                break;
            case 19:
                line += "$s3: ";
                break;
            case 20:
                line += "$s4: ";
                break;
            case 21:
                line += "$s5: ";
                break;
            case 22:
                line += "$s6: ";
                break;
            case 23:
                line += "$s7: ";
                break;
            case 24:
                line += "$t8: ";
                break;
            case 25:
                line += "$t9: ";
                break;
            case 26:
                line += "$k0: ";
                break;
            case 27:
                line += "$k1: ";
                break;
            case 28:
                line += "$gp: ";
                break;
            case 29:
                line += "$sp: ";
                break;
            case 30:
                line += "$fp: ";
                break;
            case 31:
                line += "$ra: ";
                break;

            default:
                break;
            }
            for (int j = 0; j < 32; j++)
                line += registradores[i][j];
            Log::getInstance().line(line);
        }
    };

    string **getRegistradores() { return registradores; };
    string *getSaida1() { return this->data1; };
    string *getSaida2() { return this->data2; };
    string mapeia(string reg);
};

#endif // REGISTRADORES_HPP