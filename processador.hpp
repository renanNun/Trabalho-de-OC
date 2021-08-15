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
        ALU* alu;

        string instructions;

        string Mux(string entrada0, string entrada1, string opcode)
        {
            if(opcode == "0") return entrada0;
            if(opcode == "1") return entrada1;

            cout << "Erro na operacao de controle do Multiplexador" << endl;
            return "-1";
        };



    public:
        Processador(string instructions){
            this->pc = new PC();
            this->alu = new ALU(512);

            this->instructions = instructions;
        };

        void printIF()
        {
            cout << "IF:\n\tPC -> " << pc->getPC() << endl;
        };

        void printID()
        {
            cout << "ID:\n"
                 << "PCWriteCondition -> " << UnityControl::PCWriteCond
                 << "PCWrite -> " <<  UnityControl::PCWrite
                 << "IorD -> " << UnityControl::IorD
                 << "MemRead -> " <<  UnityControl::MemRead
                 << "MemWrite -> " <<  UnityControl::MemWrite
                 << "MemReg -> " <<  UnityControl::MemReg
                 << "IRWrite -> " <<  UnityControl::IRWrite
                 << "PCSource -> " <<  UnityControl::PCSource
                 << "ALUOp -> " <<  UnityControl::ALUOp
                 << "ALUSrcB -> " <<  UnityControl::ALUSrcB
                 << "ALUSrcA -> " <<  UnityControl::ALUSrcA
                 << "RegWrite -> " <<  UnityControl::RegWrite
                 << "RegDst -> " <<  UnityControl::RegDst
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
            cout << "MEM:\n"
                 << "\tEndereco -> " << alu->getALUResult()
                 << "\n\tDado-> " << 
                 << endl;
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
                this->printRegistradores();
                exit(0);
            }
            this->pc->incremetPC();
            //Pegar a primeira Instrução aqui
            this->printIF();
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

        UnityControl getUnityControlMemWrite(){return UnityControl::MemWrite;};
         UnityControl getUnityControlMemRead(){return UnityControl::MemRead;};
};



#endif // PROCESSADOR_H