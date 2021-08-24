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

class Processador
{
private:

    const string ZERO = "00000000000000000000000000000000";
    int PC;
    int branchNextLine;
    vector<string> instructionMemory;
    string instruction_25_0 = ZERO;
    string instruction_31_26 = ZERO;
    string instruction_25_21 = ZERO;
    string instruction_20_16 = ZERO;
    string instruction_15_11 = ZERO;
    string instruction_15_0 = ZERO;
    string instruction_5_0 = ZERO;
    string instruction_15_0Extended = ZERO;
    string registerOutput1 = ZERO;
    string registerOutput2 = ZERO;
    string aluOutput = ZERO;
    string memoryOutput = ZERO;
    string multiplexador(string entrada0, string entrada1, string code);
    int multiplexador(int entrada0, int entrada1, string code);
    ALUOp aluControl(string funct);
    Registrador registrador;
    UnityControl unityControl;
    ALU *alu;
    Memory512Bytes memory;
    string split(int inicio, int fim, string line);
    string signExtend(string aux);
    void controlSignal();
    string deniedSignal(string entrada, string code);

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