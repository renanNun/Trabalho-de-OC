#include "binary.h"

binary::binary()
{

    listaDeBinarios = new vector<string>();
};

binary::~binary()
{
    listaDeBinarios->~vector();
    delete[] this->listaDeBinarios;
};

vector<string> *binary::getLista()
{

    return this->listaDeBinarios;
};

string binary::intToBinary(string inteiro){

    string r;
    int n = stoi(inteiro);
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;

};

string binary::translateCommandToBinary(string &commandToTranslate)
{

    string opcode = "";
    string regSource = "";
    string regTarget = "";
    string rd = "";
    string shamt = "";
    string funct = "";

    vector<string> *lista = new vector<string>;

    int cont = 0;
    int aux = 0;
    int iterator = 0;
    for (auto &ch : commandToTranslate)
    {
        if (ch == ' ')
        {

            lista[iterator].push_back(commandToTranslate.substr(aux, cont));
            aux = cont;
            iterator++;
        }
        else
        {
            cont++;
        }
    }

    if (lista->at(0) == "add")
    {

        opcode = "00000";
        shamt = "00000";
        funct = "100000";
    }
    else if (lista->at(0) == "sub")
    {
        opcode = "00000";
        shamt = "00000";
        funct = "100010";
    }
    else if (lista->at(0) == "and")
    {
        opcode = "00000";
        shamt = "00000";
        funct = "100001";
    }
    else if (lista->at(0) == "or")
    {
        opcode = "00000";
        shamt = "00000";
        funct = "100101";
    }
    else if (lista->at(0) == "slt")
    {
        opcode = "00000";
        shamt = "00000";
        funct = "101010";
    }
    else if (lista->at(0) == "sll")
    {
        opcode = "00000";
        shamt = intToBinary(lista->at(4));
        funct = "000000";
    }
    else if (lista->at(0) == "addi")
    {
        opcode = "001000";
        shamt = intToBinary(lista->at(4));
        funct = "100010";
    }
    else if (lista->at(0) == "lw")
    {
        opcode = "100011";
        shamt = "";
        funct = "";
    }
    else if (lista->at(0) == "sw")
    {
        opcode = "101011";
        shamt = "";
        funct = "";
    }
    else if (lista->at(0) == "beq")
    {
        opcode = "000100";
        shamt = "";
        funct = "";
    }
    else if (lista->at(0) == "bne")
    {
        opcode = "000101";
        shamt = "";
        funct = "";
    }
    else if (lista->at(0) == "j")
    {
        opcode = "000010";
        shamt = "";
        funct = "";
    }
    else if (lista->at(0) == "jr")
    {
        opcode = "000000";
        shamt = "000000000000000";
        funct = "001000";
        regTarget = "";

    }
    else if (lista->at(0) == "jal")
    {
        opcode = "000000";
        shamt = "00000";
        funct = "001001";
    }

    return opcode + regSource + regTarget + rd + shamt + funct;
};




};