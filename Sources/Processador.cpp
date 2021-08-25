#include "../Headers/Processador.hpp"

/*
    Funções Auxiliares
*/
string Processador::split(int inicio, int fim, string line)
{
    string aux;
    for (int i = inicio; i <= fim; i++)
        aux += line[i];

    return aux;
};

string turnInTheSymmetrical(string number)
{
    int first1Index = number.size() - 1;
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

int sBintoi(string binario, bool canBeNeg)
{
    if (binario.at(0) == '0' || !canBeNeg)
    {
        return stoi(binario, 0, 2);
    }
    else
    {
        binario = turnInTheSymmetrical(binario);
        return (-1*stoi(binario, 0, 2));
    }
}

string Processador::signExtend(string aux)
{
    string line = "";
    if (split(0, 0, aux) == "1")
    {
        line = split(0, 0, aux) + "1111111111111111" + split(1, 15, aux);
        return line;
    }
    else
    {
        line = "0000000000000000";
        return line + aux;
    }
    return line;
};

/*
    Etapas de processamento
*/

Processador::Processador(vector<string> &instructions)
{
    PC = -1;
    instructionMemory = instructions;
    alu = new ALU(32);
    unityControl.Jump = "0";
    unityControl.Branch = "0";
    unityControl.MemRead = "0";
    unityControl.MemWrite = "0";
    unityControl.MemtoReg = "0";
    unityControl.ALUOp = "10";
    unityControl.ALUSrc = "0";
    unityControl.RegWrite = "0";
    unityControl.RegDst = "0";
    unityControl.NotZero = "0";
};

Processador::~Processador(){

};

void Processador::IF()
{
    /*
        Próximo Comando
    */
    cout << "\tIF" << endl;
    PC = multiplexador(multiplexador(
                           PC + 1,
                           sBintoi(instruction_15_0Extended, true),
                           (unityControl.Branch == "1" && deniedSignal(alu->getZeroSignal(), unityControl.NotZero) == "1") ? "1" : "0"),
                       sBintoi(instruction_25_0, true) + 1,
                       unityControl.Jump);
    cout << "\tPC: " << PC << endl;
};

void Processador::ID()
{
    cout << endl
         << "\tID" << endl;
    /*
        Separar comando
    */
    cout << "\tComando: " << this->instructionMemory[PC] << endl;
    instruction_25_0 = split(6, 31, this->instructionMemory[PC]);
    cout << "\t\tInstruction [25-0]: " << instruction_25_0 << endl;
    instruction_31_26 = split(0, 5, this->instructionMemory[PC]);
    cout << "\t\tInstruction [31-26]: " << instruction_31_26 << endl;
    instruction_25_21 = split(6, 10, this->instructionMemory[PC]);
    cout << "\t\tInstruction [25-21]: " << instruction_25_21 << endl;
    instruction_20_16 = split(11, 15, this->instructionMemory[PC]);
    cout << "\t\tInstruction [20-16]: " << instruction_20_16 << endl;
    instruction_15_11 = split(16, 20, this->instructionMemory[PC]);
    cout << "\t\tInstruction [15-11]: " << instruction_15_11 << endl;
    instruction_15_0 = split(16, 31, this->instructionMemory[PC]);
    cout << "\t\tInstruction [15-0]: " << instruction_15_0 << endl;
    instruction_5_0 = split(26, 31, this->instructionMemory[PC]);
    cout << "\t\tInstruction [5-0]: " << instruction_5_0 << endl;
    instruction_10_6 = split(21, 25, this->instructionMemory[PC]);
    cout << "\t\tInstruction [10-6]: " << instruction_10_6 << endl;

    /*
        Pegar output do registrador
    */
    registerOutput1 = registrador.getReg(sBintoi(instruction_25_21, false));
    cout << "\t\tRegister Output 1: " << registerOutput1 << endl;
    registerOutput2 = registrador.getReg(sBintoi(instruction_20_16, false));
    cout << "\t\tRegister Output 2: " << registerOutput2 << endl;

    /*
        Extender instruction_15_0 para cálculo de funções de jump 
    */
    instruction_15_0Extended = signExtend(instruction_15_0);
    cout << "\t\tInstruction [15-11] Extended: " << instruction_15_0Extended << endl;

    /*
        Configurar unidade de controle
    */
    controlSignal();
};

void Processador::EX()
{
    cout << endl
         << "\tEX" << endl;
    /*
        Fazer operação na ALU
    */
    alu->makeOperation(registerOutput1, multiplexador4(registerOutput2, instruction_15_0Extended, instruction_10_6, "", unityControl.ALUSrc), aluControl(instruction_5_0));

    /*
        Pegar output da ALU
    */
    aluOutput = alu->getALUResult();
};

void Processador::MEM()
{
    cout << endl
         << "\tMEM" << endl;
    /*
        Fazer operção na memória
    */
    memory.makeOperation(aluOutput, registerOutput2, unityControl.MemRead, unityControl.MemWrite);

    /*
        Pegar output da memória
    */
    memoryOutput = memory.getMemData();
    if (unityControl.MemRead == "1" || unityControl.MemWrite == "1")
    {
        memory.imprimirMemoria();
    }
};

void Processador::WB()
{
    cout << endl
         << "\tWB" << endl;
    /*
        Escrever no registrador se RegWrite
    */
    if (unityControl.RegWrite == "1")
    {
        registrador.escreve(sBintoi(multiplexador(instruction_20_16, instruction_15_11, unityControl.RegDst), false), multiplexador(aluOutput, memoryOutput, unityControl.MemtoReg));
    }
    else
    {
        cout << "Não será escrito no registrador!" << endl;
    }
    registrador.imprime();
}

/*
    Pequenos hardwares
*/

string Processador::multiplexador(string entrada0, string entrada1, string code)
{
    if (code == "0")
    {
        return entrada0;
    }
    else if (code == "1")
    {
        return entrada1;
    }
    else
    {
        cout << "Não realizar essa operação no multiplexador!" << endl;
        exit(-2);
    }
};

int Processador::multiplexador(int entrada0, int entrada1, string code)
{
    if (code == "0")
    {
        return entrada0;
    }
    else if (code == "1")
    {
        return entrada1;
    }
    else
    {
        cout << "Não realizar essa operação no multiplexador!" << endl;
        exit(-2);
    }
};

string Processador::multiplexador4(string entrada0, string entrada1, string entrada2, string entrada3, string code)
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

string Processador::deniedSignal(string entrada, string code)
{
    if (code == "0")
    {
        return entrada;
    }
    else if (code == "1")
    {
        return (entrada == "1") ? "0" : "1";
    }
    else
    {
        cout << "Não realizar essa operação no deniedSignal!" << endl;
        exit(-2);
    }
}

ALUOp Processador::aluControl(string funct)
{
    if (unityControl.ALUOp == "10")
    {
        if (funct == "100000")
        {
            return ALUOp::ADD;
        }
        else if (funct == "100010")
        {
            return ALUOp::SUB;
        }
        else if (funct == "100100")
        {
            return ALUOp::AND;
        }
        else if (funct == "100101")
        {
            return ALUOp::OR;
        }
        else if (funct == "101010")
        {
            return ALUOp::SLT;
        }
        else if (funct == "000000")
        {
            return ALUOp::SLL;
        }
        else
        {
            cout << "funct inválido!\nImpossível definir o ALUOp!" << endl;
            exit(-2);
        }
    }
    else if (unityControl.ALUOp == "01")
    {
        return ALUOp::SUB;
    }
    else if (unityControl.ALUOp == "00")
    {
        return ALUOp::ADD;
    }
    else
    {
        cout << "ALUOp inválido!\nImpossível definir o ALUOp!" << endl;
        exit(-2);
    }
};

void Processador::controlSignal()
{
    /*
        Tipo R (add, sub, and, or, slt)
    */
    if (instruction_31_26 == "000000")
    {
        unityControl.Jump = "0";
        unityControl.Branch = "0";
        unityControl.MemRead = "0";
        unityControl.MemWrite = "0";
        unityControl.MemtoReg = "0";
        unityControl.ALUOp = "10";
        unityControl.ALUSrc = "00";
        unityControl.RegWrite = "1";
        unityControl.RegDst = "1";
        unityControl.NotZero = "1";
    }
    /*
        Comando sw
    */
    else if (instruction_31_26 == "101011")
    {
        unityControl.Jump = "0";
        unityControl.Branch = "0";
        unityControl.MemRead = "0";
        unityControl.MemWrite = "1";
        unityControl.MemtoReg = "0";
        unityControl.ALUOp = "00";
        unityControl.ALUSrc = "01";
        unityControl.RegWrite = "0";
        unityControl.RegDst = "0";
        unityControl.NotZero = "1";
    }
    /*
        Comando lw
    */
    else if (instruction_31_26 == "100011")
    {
        unityControl.Jump = "0";
        unityControl.Branch = "0";
        unityControl.MemRead = "1";
        unityControl.MemWrite = "0";
        unityControl.MemtoReg = "1";
        unityControl.ALUOp = "00";
        unityControl.ALUSrc = "01";
        unityControl.RegWrite = "1";
        unityControl.RegDst = "0";
        unityControl.NotZero = "1";
    }
    /*
        Comando addi
    */
    else if (instruction_31_26 == "001000")
    {
        unityControl.Jump = "0";
        unityControl.Branch = "0";
        unityControl.MemRead = "0";
        unityControl.MemWrite = "0";
        unityControl.MemtoReg = "0";
        unityControl.ALUOp = "00";
        unityControl.ALUSrc = "01";
        unityControl.RegWrite = "1";
        unityControl.RegDst = "0";
        unityControl.NotZero = "1";
    }
    /*
        Comando sll
    */
    else if (instruction_31_26 == "001000")
    {
        unityControl.Jump = "0";
        unityControl.Branch = "0";
        unityControl.MemRead = "0";
        unityControl.MemWrite = "0";
        unityControl.MemtoReg = "0";
        unityControl.ALUOp = "10";
        unityControl.ALUSrc = "10";
        unityControl.RegWrite = "1";
        unityControl.RegDst = "0";
        unityControl.NotZero = "1";
    }
    /*
        Comando beq
    */
    else if (instruction_31_26 == "001000")
    {
        unityControl.Jump = "0";
        unityControl.Branch = "1";
        unityControl.MemRead = "0";
        unityControl.MemWrite = "0";
        unityControl.MemtoReg = "0";
        unityControl.ALUOp = "01";
        unityControl.ALUSrc = "00";
        unityControl.RegWrite = "0";
        unityControl.RegDst = "0";
        unityControl.NotZero = "0";
    }
    /*
        Comando bne
    */
    else if (instruction_31_26 == "000101")
    {
        unityControl.Jump = "0";
        unityControl.Branch = "1";
        unityControl.MemRead = "0";
        unityControl.MemWrite = "0";
        unityControl.MemtoReg = "0";
        unityControl.ALUOp = "01";
        unityControl.ALUSrc = "00";
        unityControl.RegWrite = "0";
        unityControl.RegDst = "0";
        unityControl.NotZero = "1";
    }
};