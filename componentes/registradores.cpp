#include "registradores.hpp"

Registradores::Registradores()
{
    this->registradores = new string*[n];
    for(int i = 0; i < n; i++)
    {
        this->registradores[i] = new s[n];
        for(int j = 0; j < n; j++)
            this->registradores[i][j] = "0";
    }

    this->data1 = "0";
    this->data2 = "0";
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

void Registradores::writeBack(string* dataW)
{
    if(controlRegW == 1)
    {
        for(int i = 0; i < n; i++) this->registradores[regW][i] = dataW[i];
    }
}

string Registradores::mapeia(string reg)
{
    switch(reg){
        case "$zero": // 0
            return "00000";
            break;
        case "$at": // 1
            return "00001";
            break;
        case "$v0": // 2
            return "00010"
            break;
        case "$v1": // 3
            return "00011"
            break;
        case "$a0": // 4
            return "00100";
            break;
        case "$a1":// 5
            return "00101";
            break;
        case "$a2": // 6
            return "00110";
            break;
        case "$a3": // 7
            return "00111";
            break;
        case "$t0": // 8
            return "01000";
            break;
        case "$t1": // 9
            return "01001";
            break;
        case "$t2": // 10
            return "01010";
            break;
        case "$t3": // 11
            return "01011";
            break;
        case "$t4": // 12
            return "01100";
            break;
        case "$t5": // 13
            return "01101";
            break;
        case "$t6": // 14
            return "01110";
            break;
        case "$t7": // 15
            return "01111";
            break;
        case "$s0": // 16
            return "10000";
            break;
        case "$s1": // 17
            return "10001";
            break;
        case "$s2": // 18
            return "10010";
            break;
        case "$s3": // 19
            return "10011";
            break;
        case "$s4": // 20
            return "10100";
            break;
        case "$s5": // 21
            return "10101";
            break;
        case "$s6": // 22
            return "10110";
            break;
        case "$s7": // 23
            return "10111";
            break;
        case "$t8": // 24
            return "11000";
            break;
        case "$t9": // 25
            return "11001";
            break;
        case "$k0": // 26
            return "";
            break;
        case "$k1": // 27
            return "";
            break;
        case "$gp": // 28
            return "11100";
            break;
        case "$sp": // 29
            return "11101";
            break; 
        case "$fp": // 30
            return "11110";
            break;
        case "$ra": // 31
            return "11111";
            break;
        default: 
            cout << "Erro na busca do registrador " << reg << endl;
            break;
    }
}