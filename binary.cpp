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

string binary::intToBinary(string inteiro)
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

const vector<string> explode(const string& s, const char& c)
        {
            if(s == "" || s.length()<=0){
                cout << "explode(): string vazia" << endl;
                return vector<string>();
            }

            string buff{""};
            vector<string> v;


            for(auto n:s)
            {
                if(n != c) buff+=n; else
                if(n == c && buff != "") { v.push_back(buff); buff = ""; }
            }
            if(buff != "") v.push_back(buff);

            return v;
        }

string binary::translateCommandToBinary(string &commandToTranslate)
{

    string opcode = "";
    string regSource = "";
    string regTarget = "";
    string rd = "";
    string shamt = "";
    string funct = "";
    Registradores* reg = new Registradores();


    vector<string> lista =  explode(commandToTranslate,' ');
    

    if (lista.at(0) == "add")
    {
       

        opcode = "000000";
        shamt = "00000";
        funct = "100000";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(3));
        rd = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "sub")
    {
        opcode = "000000";
        shamt = "00000";
        funct = "100010";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(3));
        rd = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "and")
    {
        opcode = "000000";
        shamt = "00000";
        funct = "100001";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(3));
        rd = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "or")
    {
        opcode = "000000";
        shamt = "00000";
        funct = "100101";
       regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(3));
        rd = reg->mapeia(lista.at(1));;
    }
    else if (lista.at(0) == "slt")
    {
        opcode = "00000";
        shamt = "00000";
        funct = "101010";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(3));
        rd = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "sll")
    {
    }
    else if (lista.at(0) == "addi")
    {
        string finalString = typeIcommands(lista);
        reg->~Registradores();
        return finalString;
    }
    else if (lista.at(0) == "lw")
    {
        // string finalString = typeIcommands(lista);
        // reg->~Registradores();
        // return finalString;
    }
    else if (lista.at(0) == "sw")
    {
        // string finalString = typeIcommands(lista);
        // reg->~Registradores();
        // return finalString;
    }
    else if (lista.at(0) == "beq")
    {
        string finalString = typeIcommands(lista);
        reg->~Registradores();
        return finalString;
    }
    else if (lista.at(0) == "bne")
    {
        string finalString = typeIcommands(lista);
        reg->~Registradores();
        return finalString;
    }
    else if (lista.at(0) == "j")
    {
        string finalString = typeJcommands(lista);
        reg->~Registradores();
        return finalString;
    }
    else if (lista.at(0) == "jr")
    {
        string finalString = typeJcommands(lista);
        reg->~Registradores();
        return finalString;
    }
    else if (lista.at(0) == "jal")
    {
        string finalString = typeJcommands(lista);
        reg->~Registradores();
        return finalString;
    }

    reg->~Registradores();
    return opcode + regSource + regTarget + rd + shamt + funct;
};

string binary::typeIcommands(vector<string> lista)
{
    string opcode = "";
    string regSource = "";
    string regTarget = "";
    string offset = "";
    Registradores* reg = new Registradores();

    if (lista.at(0) == "addi")
    {
        opcode = "001000";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(1));
        offset = intToBinary(lista.at(3));
    }

    else if (lista.at(0) == "beq")
    {
        opcode = "000100";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(1));
        offset = intToBinary(lista.at(3));
    }
    else if (lista.at(0) == "bne")
    {
        opcode = "000101";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(1));
        offset = intToBinary(lista.at(3));
    }

    return opcode + regSource + regTarget + offset;
};

string binary::typeJcommands(vector<string> lista){
return "";
};