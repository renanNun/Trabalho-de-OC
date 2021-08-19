#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "PC.hpp"
#include "unityControl.hpp"
#include "ALU.hpp"
#include "binary.hpp"
#include "ALUOp.hpp"
#include "Memory512Bytes.hpp"

using namespace std;

class Processador
{
    private:
        ALU* alu;
        UnityControl uc;
        Memory512Bytes* mem;
        vector<string> instructions;

        bool strToBool(string s)
        {
            bool b = 0;
            istringstream ss(s);
            ss >> b;
            return b;
        }

        string Mux(string entrada0, string entrada1, string code)
        {
            if(code == "1") return entrada0;
            if(code == "0") return entrada1;

            return " ";
        };

        string split(int inicio, int fim, string line)
        {
            string aux;
            for(int i = inicio; i <=fim; i++)
                aux += line[i];

            return aux;
        }

        string signalExtend(string aux)
        {
            string line = "0000000000000000";

            return line + aux;
        }

        void controlSignals()
        {
            if(opcode == "000000"){
                // Instruções do tipo R
                uc.PCWriteCond = " ";
                uc.PCWrite = " ";
                uc.IorD = "0";
                uc.MemRead = " ";
                uc.MemWrite = " ";
                uc.MemReg = "0";
                uc.IRWrite = " ";
                uc.PCSource = "00";
                uc.ALUOp = "10";
                uc.ALUSrcB = "00";
                uc.ALUSrcA = "1";
                uc.RegWrite = "1";
                uc.RegDst = "1";
            }else{
                // Instrução do tipo I
                uc.PCWriteCond = " ";
                uc.PCWrite = " ";
                uc.IorD = "0";
                uc.MemRead = " ";
                uc.MemWrite = " ";
                uc.MemReg = "0";
                uc.IRWrite = " ";
                uc.PCSource = "00";
                uc.ALUOp = "10";
                uc.ALUSrcB = "10";
                uc.ALUSrcA = "1";
                uc.RegWrite = "1";
                uc.RegDst = "0";
            }
        };

        string opcode;
        string funct;
        string line;

        string register_1;
        string register_2;
    public:
        Processador(vector<string> &instructions)
        {
            this->instructions = instructions;
            alu = new ALU(512);
            mem = new Memory512Bytes();
        };
        ~Processador(){};

        void IF(){
            // Exibição do valor de PC atual
            cout <<"\nIF:\n" << "\tValor de PC: " << PC::getInstance().getPC() << endl;

            binary* bin = new binary();
            line = bin->translateCommandToBinary(this->instructions[0]);
            cout << "\tComando traduzido: " << line;
            
            opcode = bin->getOP();
            funct = bin->getFunct();

            //translateCommandToBinary(string &commandToTranslate);
            PC::getInstance().incremetPC();
        };

        void ID()
        {
            cout << "\nID:\n" << "\tOpcode: " << opcode << "\n\tFunct: " << funct;

            register_1 = split(21,25,line);
            register_2 = split(16,20,line);

            cout << "\n\tRead reg 1: " << register_1 << "\n\tRead reg 2: " << register_2;

            string inst = split(0,15,line);

            controlSignals();
            string write_register = Mux(register_2,split(11,15,line), this->uc.RegDst);
            cout << "\n\twrite register: " << write_register;

            cout << "\n\tSignal Extends: " << signalExtend(inst);

        };

        void EX() // ISSO AQUI TA MUITO CONFUSO PQ EU NAO SEI ONDE EXECUTA DIREITO
        {
            cout << "\nEX: ";

            // Executando Instruções

            if(uc.RegDst == "1")
            {
                // Tipo R
                if(funct == "100000")
                {
                    alu->makeOperation(register_1,register_2,ALUOp::ADD);
                }else if(funct == "100010")
                {
                    alu->makeOperation(register_1,register_2,ALUOp::SUB);
                }else if(funct == "100100")
                {
                    alu->makeOperation(register_1,register_2,ALUOp::AND);
                }else if(funct == "100101")
                {
                    alu->makeOperation(register_1,register_2,ALUOp::OR);
                }
            }

            if(uc.MemRead == "1" || uc.MemWrite == "1")
                alu->makeOperation(register_1,register_2,ALUOp::ADD);

            if(uc.PCSource == "10")
            {
                if(opcode == "000010")
                    alu->makeOperation(register_1,register_2,ALUOp::ADD);
            }

            cout << "\n\tAluOut: " << alu->getALUResult();
        }

        void MEM()
        {
            string aluOUT = alu->getALUResult();

            string address = Mux(PC::getInstance().getPC(),aluOUT,uc.IorD);

            string write_data;
            // Pra pegar o Write Data, eu preciso do Memory data register,
            // que eu consigo só na segunda interação?
            if(uc.MemRead == "1")
            {
                // LW
                if(opcode == "100011")
                {
                    mem->makeOperation(address, write_data, strToBool(uc.MemRead),strToBool(uc.MemWrite));
                }else if(opcode == "100000") //LB
                {

                }
            }else if(uc.MemWrite == "1")
            {
                // SW
                if(opcode == "101011")
                {

                }else if(opcode == "101000") //SB
                {

                }
            }

            cout << "Memoria: ";
        }

        void WR()
        {
            //if(uc.MemReg == "0")
            
            //if(uc.RegDst == "0")

            //if(uc.RegDst == "1")
        }


        string getUnityControlMemWrite(){return this->uc.MemWrite;};
        string getUnityControlMemRead(){return this->uc.MemRead;};
};



#endif // PROCESSADOR_H