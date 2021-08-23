#include "../Headers/Processador.hpp"

/*
    Funções Auxiliares
*/
string split(int inicio, int fim, string line)
{
    string aux;
    for (int i = inicio; i <= fim; i++)
        aux += line[i];

    return aux;
};

string signExtend(string aux)
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
};

/*
    Etapas de processamento
*/

Processador::Processador(vector<string> &instructions)
{
    PC = -1;
    instructionMemory = instructions;
    alu = new ALU(32);
};

Processador::~Processador()
{

};

void Processador::IF()
{
    /*
        Próximo Comando
    */
    PC = multiplexador(multiplexador(PC + 1, stoi(instruction_15_0Extended, 0, 2) + PC + 1 , (unityControl.Branch == "1" && alu->getZeroSignal() == "1") ? "1" : "0"), 
    stoi(instruction_25_0, 0, 2) + 1, 
    unityControl.Jump);
};

void Processador::ID()
{
    /*
        Separar comando
    */
    instruction_25_0 = split(0, 25, this->instructionMemory[PC]);
    instruction_31_26 = split(26, 31, this->instructionMemory[PC]);
    instruction_25_21 = split(21, 25, this->instructionMemory[PC]);
    instruction_20_16 = split(20, 16, this->instructionMemory[PC]);
    instruction_15_11 = split(11, 15, this->instructionMemory[PC]);
    instruction_15_0 = split(0, 15, this->instructionMemory[PC]);
    instruction_5_0 = split(0, 5, this->instructionMemory[PC]);

    /*
        Pegar output do registrador
    */
    registerOutput1 = registrador.getReg(stoi(instruction_25_21, 0, 2));
    registerOutput2 = registrador.getReg(stoi(instruction_20_16, 0, 2));

    /*
        Extender instruction_15_0 para cálculo de funções de jump 
    */
    instruction_15_0Extended = signExtend(instruction_15_0);
};

void Processador::EX()
{
    /*
        Fazer operação na ALU
    */
    alu->makeOperation(registerOutput1, multiplexador(registerOutput2, instruction_15_0Extended, unityControl.ALUSrc), aluControl(instruction_5_0));

    /*
        Pegar output da ALU
    */
    aluOutput = alu->getALUResult();
};

void Processador::MEM()
{
    /*
        Fazer operção na memória
    */
    memory.makeOperation(aluOutput, registerOutput2, unityControl.MemRead, unityControl.MemWrite);

    /*
        Pegar output da memória
    */
    memoryOutput = memory.getMemData();
};

void Processador::WB()
{
    /*
        Escrever no registrador se RegWrite
    */
    if (unityControl.RegWrite == "1")
    {
        registrador.escreve(stoi(multiplexador(instruction_20_16, instruction_15_11, unityControl.RegDst)), multiplexador(aluOutput, memoryOutput, unityControl.MemtoReg));
    }
    else
    {
        cout << "Não será escrito no registrador!" << endl;
        exit(-2);
    }
}

/*
    Pequenos hardwares
*/

string Processador::multiplexador(string entrada0, string entrada1, string code)
{
    if (code == "0"){
        return entrada0;
    }
    else if (code == "1"){
        return entrada1;
    } else {
        cout << "Não realizar essa operação no multiplexador!" << endl;
        exit(-2);
    }
};

int Processador::multiplexador(int entrada0, int entrada1, string code)
{
    if (code == "0"){
        return entrada0;
    }
    else if (code == "1"){
        return entrada1;
    } else {
        cout << "Não realizar essa operação no multiplexador!" << endl;
        exit(-2);
    }
        
};

ALUOp Processador::aluControl(string funct)
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
    else if (funct == "000000")
    {
        return ALUOp::SLL;
    }
    else if (funct == "101010")
    {
        return ALUOp::SLT;
    }
    else
    {
        cout << "funct inválido!\nImpossível definir o ALUOp!" << endl;
        exit(-2);
    }
};
