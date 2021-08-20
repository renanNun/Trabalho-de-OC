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
        Registradores* reg;
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

        string MuxSourceB(string entrada0, string entrada1, string entrada2,string entrada3, string code)
        {
            if(code == "00") return entrada0;
            if(code == "01") return entrada1;
            if(code == "10") return entrada2;
            if(code == "11") return entrada3;

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
            if(opcode == "000000" && funct != "001000"){
                // Instruções do tipo R
                cout << "\n\tComando do Tipo R";
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
            }else if(opcode == "101011" || opcode == "101000"){
                // Instruções do tipo Store
                cout << "\n\tComando do Tipo Store";
                uc.PCWriteCond = " ";
                uc.PCWrite = " ";
                uc.IorD = "1";
                uc.MemRead = " ";
                uc.MemWrite = "1";
                uc.MemReg = "0";
                uc.IRWrite = " ";
                uc.PCSource = "00";
                uc.ALUOp = "00";
                uc.ALUSrcB = "10";
                uc.ALUSrcA = "1";
                uc.RegWrite = " ";
                uc.RegDst = " ";
            }else if(opcode == "100011" || opcode == "100000"){
                // Instruções do tipo Load
                cout << "\n\tComando do Tipo Load";
                uc.PCWriteCond = " ";
                uc.PCWrite = " ";
                uc.IorD = "1";
                uc.MemRead = "1";
                uc.MemWrite = " ";
                uc.MemReg = "1";
                uc.IRWrite = " ";
                uc.PCSource = "00";
                uc.ALUOp = "00";
                uc.ALUSrcB = "10";
                uc.ALUSrcA = "1";
                uc.RegWrite = "1";
                uc.RegDst = " ";
            }else{
                // Instrução do tipo I
                cout << "\n\tComando do Tipo I";
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

        string sinalExtends;
        string write_data;

        string shiftLeftLogical(string a, string b)
        {
            string result = "";
            int shiftAmount = stoi(b, 0, 2);
            cout << shiftAmount << endl;
            for (int i = 32; i >= 0; i--)
            {
                result += a[(i + shiftAmount) % 32];
            }

            return result;
        }
    public:
        Processador(vector<string> &instructions)
        {
            this->instructions = instructions;
            alu = new ALU(512);
            mem = new Memory512Bytes();
            reg = new Registradores();
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
            sinalExtends = signalExtend(inst);
            cout << "\n\tSignal Extends: " << sinalExtends;

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

            if(uc.PCSource == "01")
            {
                if(opcode == "000010")
                    alu->makeOperation(register_1,register_2,ALUOp::ADD);
            }

            if(uc.PCSource == "10")
            {
                if(opcode == "000010")
                {
                    PC::getInstance().incremetPC();
                }else if(opcode == "000011")
                {
                    // Fazer Jal
                }else{
                    // Fazer Junior
                }
               
            }

            cout << "\n\tAluOut: " << alu->getALUResult();
        }

        bool validaBoolean(string a)
        {
            if(a == "1")
                return strToBool(a);
            else if(a == "0")
                return strToBool(a);

            return false;
        }
        
        string intToBinary16B(string inteiro)
        {

            string r;
            int n = stoi(inteiro);
            while (n != 0)
            {
                r = (n % 2 == 0 ? "0" : "1") + r;
                n /= 2;
            }

            return r;
        };

        void MEM()
        {
            cout << "\nMEM:";
            string aluOUT = alu->getALUResult();
            string aux = to_string(PC::getInstance().getPC());
            string address = Mux(intToBinary16B(aux),aluOUT,uc.IorD);
            //cout << "\n2";
            string SLtwo = shiftLeftLogical(sinalExtends,"0000000000000010");
            //cout << "\n3";
            write_data = MuxSourceB(register_2,"4",sinalExtends,SLtwo,uc.ALUSrcB);
            // Pra pegar o Write Data, eu preciso do Memory data register,
            // que eu consigo só na segunda interação?
            //cout << "\nEntrar nos if";
            if(uc.MemRead == "1")
            {
                // LW
                if(opcode == "100011")
                {
                    cout << "LW";
                    mem->makeOperation(address, write_data, validaBoolean(uc.MemRead),validaBoolean(uc.MemWrite));
                }else if(opcode == "100000") //LB
                {
                    cout << "\n\tLB";
                    cout << "\n\tADDRESS: " << address;
                    cout << "\n\twrite_data: " << write_data;
                    cout << "\n\tMEMREAD: " << validaBoolean(uc.MemRead);
                    cout << "\n\tMEMWRITE: " << validaBoolean(uc.MemWrite) << endl;
                    mem->makeOperation(address, write_data, validaBoolean(uc.MemRead),validaBoolean(uc.MemWrite));
                }
            }else if(uc.MemWrite == "1")
            {
                // SW
                if(opcode == "101011")
                {
                    mem->makeOperation(address, write_data, validaBoolean(uc.MemRead),validaBoolean(uc.MemWrite));
                }else if(opcode == "101000") //SB
                {
                    mem->makeOperation(address, write_data, validaBoolean(uc.MemRead),validaBoolean(uc.MemWrite));
                }
            }

            cout << "\nMemoria: ";
            //mem->imprimirMemoria();
        } 

        void WR()
        {
            cout << "\nWR:";
            if(uc.MemReg == "0"){
                write_data = alu->getALUResult();
                cout << "\n\tWrite Data: " << write_data;
            }

            if(uc.RegDst == "0")
                reg->escreve(convertBin(split(16,20,line)),write_data);
            if(uc.RegDst == "1")
                reg->escreve(convertBin(split(11,15,line)),write_data);
        }

        int convertBin(string address)
        {
            int dec = 0;
            int bin = stoi(address);
            for(int i = 0; i < bin ;i++)
            {
                dec = dec + pow(2,i) * (bin % 10);
                bin = bin/10;
            }

            return bin;
        }

        string getUnityControlMemWrite(){return this->uc.MemWrite;};
        string getUnityControlMemRead(){return this->uc.MemRead;};
};



#endif // PROCESSADOR_H