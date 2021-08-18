#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <iostream>
#include <string>

#include "PC.hpp"
#include "unityControl.hpp"
#include "ALU.hpp"
#include "binary.hpp"

using namespace std;

class Processador
{
    private:
        PC* pc;
        ALU* alu;
        UnityControl uc;

        string instructions;

        string Mux(string entrada0, string entrada1, string opcode)
        {
            if(opcode == "0") return entrada0;
            if(opcode == "1") return entrada1;

            cout << "Erro na operacao de controle do Multiplexador" << endl;
            return "-1";
        };

        void controlSignals()
        {
            binary* bin = new binary();
            string mips = bin->translateCommandToBinary(instructions);

            string opcode = bin->getOP();
            string funct = bin->getFunct();

            if(opcode == "000000" && funct != "001000")
            {
                // Tipo R
                this->uc.PCWriteCond = "x";
                this->uc.PCWrite = "x";
                this->uc.IorD = "0";
                this->uc.MemRead = "x";
                this->uc.MemWrite = "x";
                this->uc.MemReg = "0";
                this->uc.IRWrite = "x";
                this->uc.PCSource = "00";
                this->uc.ALUOp = "10";
                this->uc.ALUSrcB = "00";
                this->uc.ALUSrcA = "1";
                this->uc.RegWrite = "1";
                this->uc.RegDst = "1";
            }else if(opcode == "100011" || opcode == "100000")
            {
                // Tipo Load
                this->uc.PCWriteCond = "x";
                this->uc.PCWrite = "x";
                this->uc.IorD = "1";
                this->uc.MemRead = "1";
                this->uc.MemWrite = "x";
                this->uc.MemReg = "1";
                this->uc.IRWrite = "x";
                this->uc.PCSource = "00";
                this->uc.ALUOp = "00";
                this->uc.ALUSrcB = "10";
                this->uc.ALUSrcA = "1";
                this->uc.RegWrite = "1";
                this->uc.RegDst = "0";
            }else if(opcode == "000010" || opcode == "000011" ||
                     (opcode == "000000" && funct == "001000"))
            {
                // Instrução de desvio
            }else if(opcode == "000100" || opcode == "000101")
            {
                // Instrução de desvio
            }else{
                // Instrução do tipo I
                this->uc.PCWriteCond = "x";
                this->uc.PCWrite = "x";
                this->uc.IorD = "0";
                this->uc.MemRead = "x";
                this->uc.MemWrite = "x";
                this->uc.MemReg = "0";
                this->uc.IRWrite = "x";
                this->uc.PCSource = "00";
                this->uc.ALUOp = "10";
                this->uc.ALUSrcB = "10";
                this->uc.ALUSrcA = "1";
                this->uc.RegWrite = "1";
                this->uc.RegDst = "0";
            }

        }

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
                 << "PCWriteCondition -> " << this->uc.PCWriteCond
                 << "PCWrite -> " <<  this->uc.PCWrite
                 << "IorD -> " << this->uc.IorD
                 << "MemRead -> " <<  this->uc.MemRead
                 << "MemWrite -> " <<  this->uc.MemWrite
                 << "MemReg -> " <<  this->uc.MemReg
                 << "IRWrite -> " <<  this->uc.IRWrite
                 << "PCSource -> " <<  this->uc.PCSource
                 << "ALUOp -> " <<  this->uc.ALUOp
                 << "ALUSrcB -> " <<  this->uc.ALUSrcB
                 << "ALUSrcA -> " <<  this->uc.ALUSrcA
                 << "RegWrite -> " <<  this->uc.RegWrite
                 << "RegDst -> " <<  this->uc.RegDst
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
                 << "\n\tDado-> "
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

       string getUnityControlMemWrite(){return this->uc.MemWrite;};
       string getUnityControlMemRead(){return this->uc.MemRead;};
};



#endif // PROCESSADOR_H