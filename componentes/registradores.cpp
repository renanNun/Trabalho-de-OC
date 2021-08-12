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

    if(reg == "$zero"){
            return "00000";
    }else if(reg == "$at"){
            return "00001";
    }else if(reg =="$v0" ){
            return "00010"
    }else if(reg == "$v1")
    {
        return "00011"
    }else if(reg == "$a0")
    {
        return "00100";
    }else if(reg == "$a1"){
            return "00101";
    }else if(reg == "$a2")
    {
        return "00110";
    }else if(reg == "$a3")
    {
        return "00111";
    }else if(reg == "$t0")
    {
        return "01000";
    }else if(reg == "$t1")
    {
        return "01001";
    }else if(reg == "$t2")
    {
            return "01010";
    }else if(reg == "$t3")
    {
            return "01011";
    }else if(reg == "$t4")
    {
        return "01100";
    }else if(reg == "$t5")
    {
        return "01101";
    }else if(reg == "$t6")
    {
            return "01110";
    }else if(reg == "$t7")
    {
        return "01111";
    }else if(reg == "$s0")
    {
        return "10000";
    }else if(reg == "$s1")
    {
        return "10001";
    }else if(reg == "$s2")
    {
            return "10010";
    }else if(reg == "$s3")
    {
            return "10011";
    }else if(reg == "$s4")
    {
        return "10100";
    }else if(reg == "$s5")
    {
            return "10101";
    }else if(reg == "$s6")
    {
            return "10110";
    }else if(reg == "$s7")
    {
        return "10111";
    }else if(reg == "$t8")
    {
        return "11000";
    }else if(reg == "$t9")
    {
        return "11001";
    }else if(reg == "$k0")
    {
            return "";
    }else if(reg == "$k1")
    {
        return "";
    }else if(reg == "$gp")
    {
        return "11100";
    }else if(reg == "$sp")
    {
        return "11101";
    }else if(reg == "$fp")
    {
        return "11110";
    }else if(reg == "$ra")
    {
        return "11111";
    }else{
        cout << "Erro na busca do registrador " << reg << endl;
    }
}