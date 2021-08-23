#ifndef PROCESSADOR_HPP
#define PROCESSADOR_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include <fstream>

#include "PC.hpp"
#include "UnityControl.hpp"
#include "ALU.hpp"
#include "ALUOp.hpp"
#include "Memory512Bytes.hpp"
#include "Log.hpp"
#include "Registrador.hpp"

using namespace std;

class Processador{
    private:
        int PC;
        int branchNextLine;
        vector<string> instructionMemory;
        string instruction_25_0;
        string instruction_31_26;
        string instruction_25_21;
        string instruction_20_16;
        string instruction_15_11;
        string instruction_15_0;
        string instruction_5_0;
        string instruction_15_0Extended;
        string registerOutput1;
        string registerOutput2;
        string aluOutput;
        string memoryOutput;
        string multiplexador(string entrada0, string entrada1, string code);
        int multiplexador(int entrada0, int entrada1, string code);
        ALUOp aluControl(string funct);
        Registrador registrador;
        UnityControl unityControl;
        ALU* alu;
        Memory512Bytes memory;
        
    public:
        Processador(vector<string> &instructions);
        ~Processador();
        void IF();
        void ID();
        void EX();
        void MEM();
        void WB();

};

#endif