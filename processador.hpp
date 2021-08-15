#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <iostream>
#include <string>

#include "PC.hpp"
#include "unityControl.hpp"
#include "ALU.hpp"

using namespace std;

class Processador
{
    private:
        PC* pc;
        UnityControl* uc;
        ALU* alu;

        string Mux(string entrada0, string entrada1, string opcode)
        {
            if(opcode == "0") return entrada0;
            if(opcode == "1") return entrada1;

            cout << "Erro na operacao de controle do Multiplexador" << endl;
            return "-1";
        };

    public:
        Processador(){
            pc = new PC();
            uc = new UnityControl();
            alu = new ALU(512);
        };

        void printIF()
        {
            cout << "IF:\n\tPC -> " << pc->getPC() << endl;
        };

        void printID()
        {
            cout << "ID:\n"
                 << "PCWriteCondition -> " 
                 << "IorD -> "
                 << "MemRead -> "
                 << "MemWrite -> "
                 << "MemReg -> "
                 << "IRWrite -> "
                 << "CauseWrite -> "
                 << "IntCause -> "
                 << "EPCWrite -> "
                 << "PCSource -> "
                 << "AluOP -> "
                 << "RegWrite -> "
                 << "RegDst -> "
                 << endl;
        };

        void printEx()
        {
            cout << "EX:\n"
                 << "\tAluOut -> " << alu->getALUResult()
                 << "\n\tZero -> " << alu->getZeroSignal() 
                 << endl;
        };

        void printMEM()
        {

        };

        void printWR()
        {

        };

        void printRegistradores()
        {

        };

        void IF(){
            if(pc->getPC() < 0)
            {
                
            }
        };

        void ID()
        {

        };

        void EX()
        {

        };

        void MEM()
        {

        };

        void MR()
        {

        };

        UnityControl* getUnityControl(){return this->uc;};
};



#endif // PROCESSADOR_H