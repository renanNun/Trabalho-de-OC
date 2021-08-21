#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <fstream>

#include "PC.hpp"
#include "unityControl.hpp"
#include "ALU.hpp"
#include "binary.hpp"
#include "ALUOp.hpp"
#include "Memory512Bytes.hpp"
#include "Log.hpp"

using namespace std;

class Processador
{
private:
    ALU *alu;
    UnityControl uc;
    Memory512Bytes mem;
    Registradores *reg;
    vector<string> instructions;
    string type;
    bool strToBool(string s)
    {
        bool b = 0;
        istringstream ss(s);
        ss >> b;
        return b;
    };

    string Mux(string entrada0, string entrada1, string code)
    {
        if (code == "0")
            return entrada0; 
        if (code == "1")
            return entrada1;

        return " ";
    };

    string MuxSourceB(string entrada0, string entrada1, string entrada2, string entrada3, string code)
    {
        if (code == "00")
            return entrada0;
        if (code == "01")
            return entrada1;
        if (code == "10")
            return entrada2;
        if (code == "11")
            return entrada3;

        return " ";
    };

    string split(int inicio, int fim, string line)
    {
        string aux;
        for (int i = inicio; i <= fim; i++)
            aux += line[i];

        return aux;
    };

    string signalExtend(string aux)
    {
        string line = "";
        //cout << "AUX: " << aux;
        if(split(0,0,aux) == "1")
        {
            //cout << "\nVEMSPC\n" << endl;
            line = split(0,0,aux) + "1111111111111111" + split(1,15,aux);
            //cout << "AUX: " << line << endl;
            return line;
        }else{
            line = "0000000000000000";

             return line + aux;
        }
    };

    void controlSignals()
    {
        if (opcode == "000000")
        {
            // Instruções do tipo R
            type = "R";
            cout << "\n\tComando do Tipo R";
            uc.PCWriteCond = "x";
            uc.PCWrite = "x";
            uc.IorD = "0";
            uc.MemRead = "x";
            uc.MemWrite = "x";
            uc.MemReg = "0";
            uc.IRWrite = "x";
            uc.PCSource = "00";
            uc.ALUOp = "10";
            uc.ALUSrcB = "00";
            uc.ALUSrcA = "1";
            uc.RegWrite = "1";
            uc.RegDst = "1";
        }
        else if (opcode == "101011" || opcode == "101000")
        {
            // Instruções do tipo Store
            type = "Store";
            cout << "\n\tComando do Tipo Store";
            uc.PCWriteCond = "x";
            uc.PCWrite = "x";
            uc.IorD = "1";
            uc.MemRead = "x";
            uc.MemWrite = "1";
            uc.MemReg = "0";
            uc.IRWrite = "x";
            uc.PCSource = "00";
            uc.ALUOp = "00";
            uc.ALUSrcB = "10";
            uc.ALUSrcA = "1";
            uc.RegWrite = "x";
            uc.RegDst = "x";
        }
        else if (opcode == "100011" || opcode == "100000")
        {
            // Instruções do tipo Load
            type = "L";
            cout << "\n\tComando do Tipo Load";
            uc.PCWriteCond = "x";
            uc.PCWrite = "x";
            uc.IorD = "1";
            uc.MemRead = "1";
            uc.MemWrite = "x";
            uc.MemReg = "1";
            uc.IRWrite = "x";
            uc.PCSource = "00";
            uc.ALUOp = "00";
            uc.ALUSrcB = "10";
            uc.ALUSrcA = "1";
            uc.RegWrite = "1";
            uc.RegDst = "x";
        }
        else if (opcode == "000010" || opcode == "000011")
        {
            type = "J";
            cout << "\n\tComando do Tipo J";
            uc.PCWriteCond = "x"; // voltar
            uc.PCWrite = "x";     // voltar
            uc.IorD = "x";        // voltar
            uc.MemRead = "0";
            uc.MemWrite = "0";
            uc.MemReg = "x";
            uc.IRWrite = "x";  // voltar
            uc.PCSource = "x"; // voltar
            uc.ALUOp = "x";
            uc.ALUSrcB = "x";
            uc.ALUSrcA = "x";
            uc.RegWrite = "0";
            uc.RegDst = "x";
        }
        else
        {
            // Instrução do tipo I
            type = "I";
            cout << "\n\tComando do Tipo I";
            uc.PCWriteCond = "x";
            uc.PCWrite = "x";
            uc.IorD = "0";
            uc.MemRead = "x";
            uc.MemWrite = "x";
            uc.MemReg = "0";
            uc.IRWrite = "x";
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
    string write_register;
    int k;
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
    };

    string rt, rd, rs, immediate,shifamout;
    string Linhas_para_pular;
    bool seVaiPular;
    int xd;
    string Arquivo;
public:
    Processador(vector<string> &instructions)
    {
        k = 0;
        this->instructions = instructions;
        this->alu = new ALU(32);
        this->reg = new Registradores();
    };
    ~Processador(){};

    std::fstream saida;
    bool not_exec = false;
    bool fim = false;

    void IF()
    {
        not_exec = false;
        // Exibição do valor de PC atual
        Arquivo = "\nIF:\n\tValor de PC: " +  to_string(PC::getInstance().getPC());
        
        Log::getInstance().line(Arquivo);
        line = "";
        binary *bin = new binary();
        Arquivo = "";
        Arquivo = "Começa a instrucao aqui: " + this->instructions[k];
        Log::getInstance().line(Arquivo);
        line = bin->translateCommandToBinary(this->instructions[k]);
        Arquivo = "";
        Arquivo =  "\tComando traduzido: " + line;
        Log::getInstance().line(Arquivo);

        opcode = bin->getOP();
        funct = bin->getFunct();

        //translateCommandToBinary(string &commandToTranslate);
        PC::getInstance().incremetPC();
        if(line == "11111111111111111111111111111111"){
            not_exec = true;
            // PC antigo + linhas pra pular
            PC::getInstance().incremetPC();
            cout<< "LINHAS PARA PULAR:" <<Linhas_para_pular<<endl;
            if(split(0,0,Linhas_para_pular) == "1")
            {
                xd = stoi(turnInTheSymmetrical(Linhas_para_pular));
                PC::getInstance().setPCInt((-1) * xd);
            }else{
                xd = stoi(Linhas_para_pular);
                PC::getInstance().setPCInt(xd);
            }
            k = PC::getInstance().getPC();
        }else{
            cout << "\nIncrementando comando\n";
            k++;
        }
    };

    string turnInTheSymmetrical(string number)
    {
        int first1Index = sizeof(number) - 1;
        while (number[first1Index] != '1')
        {
            first1Index--;
        }
        for (int i = first1Index - 1; i >= 0; i--)
        {
            number[i] = (number[i] == '0') ? '1' : '0';
        }
        return number;
    };

    void ID()
    {
        Arquivo = "";
        Arquivo = "\nID:\n\tOpcode: " + opcode + "\n\tFunct: " + funct;
        Log::getInstance().line(Arquivo);
        controlSignals();

        if (type == "R")
        {
            rs = split(6, 10, line);
            rt = split(11, 15, line);
            rd = split(16, 20, line);
            shifamout = split(21, 25, line);
            cout << "\n\trs: " << rs
                 << "\n\trt: " << rt
                 << "\n\trd: " << rd
                 << "\n\tshifaumout: " << shifamout;
        }
        else if (type == "Store")
        {
            rs = split(6, 10, line);
            rt = split(11, 15, line);
            immediate = split(16,31,line);
            cout << "\n\trs: " << rs
                 << "\n\trt: " << rt
                 << "\n\trd: " << immediate;
        }
        else if (type == "L")
        {
            rs = split(6, 10, line);
            rt = split(11, 15, line);
            immediate = split(16,31,line);
            write_register = split(0,15,line);
            cout << "\n\trs: " << rs
                 << "\n\trt: " << rt
                 << "\n\trd: " << immediate;
        }
        else if (type == "J")
        {
            register_1 = split(7,31,line);
            register_2 = split(7,31,line);
        }
        else
        {
            rs = split(6, 10, line);
            rt = split(11, 15, line);
            immediate = split(16,31,line);

            cout << "\n\trs: " << rs
                 << "\n\trt: " << rt;
        }

        string inst = split(15, 31, line);

        string write_register = Mux(register_2, split(26, 31, line), this->uc.RegDst);
        cout << "\n\twrite register: " << write_register;
        sinalExtends = signalExtend(inst);
        cout << "\n\tSignal Extends: " << sinalExtends;
    };

    void EX() // ISSO AQUI TA MUITO CONFUSO PQ EU NAO SEI ONDE EXECUTA DIREITO
    {
        Arquivo = "";
        Arquivo = "\nEX: ";
        Log::getInstance().line(Arquivo);

        if (uc.ALUSrcA == "0")
            register_1 = reg->getReg(convertBin(intToBinary16B(to_string(PC::getInstance().getPC()))));
        else{
            cout << "RS: " << rs << endl;
            register_1 = reg->getReg(convertBin(rs));
        }
            
        register_2 = reg->getReg(convertBin(rt));
        /*if (uc.ALUSrcB == "00")
            
        else if (uc.ALUSrcB == "01")
        {
            register_2 = "00000000000000000000000000000100";
        }
        else if (uc.ALUSrcB == "10")
            register_2 = sinalExtends;
        else
            register_2 = shiftLeftLogical(sinalExtends, "0000000000000010");*/

        if (uc.RegDst == "1")
        {
            // Tipo R
            if (funct == "100000")
            {
                alu->makeOperation(register_1, register_2, ALUOp::ADD);
            }
            else if (funct == "100010")
            {
                alu->makeOperation(register_1, register_2, ALUOp::SUB);
            }
            else if (funct == "100100")
            {
                alu->makeOperation(register_1, register_2, ALUOp::AND);
            }
            else if (funct == "100101")
            {
                alu->makeOperation(register_1, register_2, ALUOp::OR);
            }else if(funct == "000000")
            {
                register_1 = reg->getReg(convertBin(rt));
                alu->makeOperation(register_1, shifamout, ALUOp::SLL);
            }else if(funct == "101010"){
                alu->makeOperation(register_1, register_2, ALUOp::SLT);
            }
        }

        // Tipo I
        if(type == "I")
        {
           // cout << "IMEDIATE: " << immediate << endl;
            string sinalExtendido = signalExtend(immediate);
            //cout << "SINAL EXTEN: " << sinalExtendido << endl;
            //cout << "REG 1: " << register_1 << endl;
            if(opcode == "001000")
            {
                alu->makeOperation(sinalExtendido,register_1,ALUOp::ADD);
            }
        }

        //Store
        if(type == "Store"){
            cout << "IMEDIATE: " << immediate << endl;
            string sinalExtendido = signalExtend(immediate);
            cout << "SINAL EXTEN: " <<  sinalExtendido << endl;
            cout << "REG 1: " << register_1 << endl;

            alu->makeOperation(sinalExtendido,register_1,ALUOp::ADD);
        }

        //LW
        if(type == "L"){
            cout << "IMEDIATE: " << immediate << endl;
            string sinalExtendido = signalExtend(immediate);
            cout << "SINAL EXTEN: " << sinalExtendido << endl;
            cout << "REG 1: " << register_1 << endl;

            alu->makeOperation(sinalExtendido,register_1,ALUOp::ADD);
        }


        if (uc.MemRead == "1" || uc.MemWrite == "1"){
            //cout << "Entrou no MEMREAD" << endl;
            if(type != "Store")
                alu->makeOperation(register_1, register_2, ALUOp::ADD);
        }

        if (uc.PCSource == "01")
        {
            if (opcode == "000010")
                alu->makeOperation(register_1, register_2, ALUOp::ADD);
        }

        if (uc.PCSource == "10")
        {
            if (opcode == "000010") // Tipo J
            {
                PC::getInstance().incremetPC(); // J
            }
            else if (opcode == "000011") //  Tipo R
            {
                // Jal
                reg->escreve(convertBin("0000000000011111"), intToBinary16B(to_string(PC::getInstance().getPC())));
            }
            else
            {
                // Junior
                PC::getInstance().setPC(intToBinary16B(rs));
            }
        }

        // Branch, Beq, Bnq
        if(opcode == "000101") // BNE
        {
            alu->makeOperation(register_1, register_2, ALUOp::SUB);
            Linhas_para_pular = immediate;
            seVaiPular = alu->getZeroSignal();
        }else if(opcode == "000100"){ // BNQ
            alu->makeOperation(register_1, register_2, ALUOp::SUB);
            cout<<"Imediate:" <<immediate<<endl;
            Linhas_para_pular = immediate;
            seVaiPular = !alu->getZeroSignal();
        }

        cout << "\n\tAluOut: " << alu->getALUResult();
    };


    bool validaBoolean(string a)
    {
        if (a == "1")
            return strToBool(a);
        else if (a == "0")
            return strToBool(a);

        return false;
    };

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
        Arquivo = "";
        Arquivo = "\nMEM: ";
        Log::getInstance().line(Arquivo);
        string aluOUT = alu->getALUResult();
        string aux = to_string(PC::getInstance().getPC());
        string address = aluOUT;
        string SLtwo = shiftLeftLogical(sinalExtends, "0000000000000010");
        write_data = register_2;
        cout << "WD: " << write_data << endl;
        int value;
        string aux2;
        string aux3;
        if (uc.MemRead == "1")
        {
            // LW
            if (opcode == "100011")
            {
                cout << "LW";
                // address + immediate/4

                /*value = convertBin(immediate)/4;
                cout << "\nValue: " << value << endl;
                aux2 = convertExtend16(value); 
                cout << "AUX: " << aux2 << endl;
                alu->makeOperation(address, aux2,ALUOp::ADD);
                aux3 = alu->getALUResult();
                cout << "Endereco: " << aux3 << endl;*/
                mem.makeOperation(aluOUT, write_data, validaBoolean(uc.MemRead), validaBoolean(uc.MemWrite));
            }
            else if (opcode == "100000") //LB
            {
                //cout << "\nIMPRIMINDO MEMORIA\n";
                //mem.imprimirMemoria();
                mem.makeOperation(address, write_data, validaBoolean(uc.MemRead), validaBoolean(uc.MemWrite));
            }
        }
        else if (uc.MemWrite == "1")
        {
            // SW
            if (opcode == "101011")
            {
                cout << "\nADDRESS: " << address << endl;
                mem.makeOperation(address, write_data, validaBoolean(uc.MemRead), validaBoolean(uc.MemWrite));
            }
            else if (opcode == "101000") //SB
            {
                mem.makeOperation(address, write_data, validaBoolean(uc.MemRead), validaBoolean(uc.MemWrite));
            }
        }

        cout << "\n\tMemoria: \n";
        mem.imprimirMemoria();
    };

    string convertExtend16(int inteiro)
    {
        string r = "";
        int n = inteiro;
        while (n != 0)
        {
            r = (n % 2 == 0 ? "0" : "1") + r;
            n /= 2;
        }

        string sixteenbits = "";
        cout << "R: " << r << endl;
        if (r.size() < 16)
        {

            for (int i = r.size(); i < 16; i++)
            {
                sixteenbits = "0" + sixteenbits;
            }

            r = sixteenbits + r;
        }
        return r;
    }

    void WR()
    {
        Arquivo = "";
        Arquivo = "\nWR: ";
        Log::getInstance().line(Arquivo);
        if (uc.MemReg == "0")
        {
            write_data = alu->getALUResult();
            cout << "\n\tWrite Data: " << write_data;
        }

        if (uc.RegDst == "0")
        {
            //cout << "\nEntrou em A: " << convertBin(split(11, 15, line)) << endl;
            reg->escreve(convertBin(split(11, 15, line)), write_data);
        }
        if (uc.RegDst == "1")
        {
            //cout << "\nEntrou em A: " << rd << endl;
            reg->escreve(convertBin(rd), write_data);
        }

        Arquivo = "";
        Arquivo = "\n\tImprimindo Registradores: \n";
        Log::getInstance().line(Arquivo);
        reg->imprime();
    };

    int convertBin(string address)
    {
        int bin = std::stoi(address, nullptr, 2);
        return bin;
    };

    string getUnityControlMemWrite() { return this->uc.MemWrite; };
    string getUnityControlMemRead() { return this->uc.MemRead; };
    string getUnityControlRegWrite() { return this->uc.RegWrite; };

    void printUnityControl()
    {
        cout << "Imprimindo UC\n"
            << uc.PCWriteCond << "\n"
            << uc.PCWrite  << "\n"
            << uc.IorD << "\n"
            << uc.MemRead  << "\n"
            << uc.MemWrite << "\n"
            << uc.MemReg << "\n"
            << uc.IRWrite  << "\n"
            << uc.PCSource  << "\n"
            << uc.ALUOp  << "\n"
            << uc.ALUSrcB << "\n"
            << uc.ALUSrcA << "\n"
            << uc.RegWrite << "\n"
            << uc.RegDst << "\n";
    }
};

#endif // PROCESSADOR_H