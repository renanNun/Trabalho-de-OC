#include "binary.hpp"

binary::binary()
{

    listaDeBinarios = new vector<string>();
    opcode = "";
    funct = "";
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

string binary::intToBinary16B(string inteiro)
{

    string r;
    int n = stoi(inteiro);
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }

    string sixteenbits;

    if (r.size() < 16)
    {

        for (int i = r.size(); i < 16; i++)
        {
            sixteenbits = "0" + sixteenbits;
        }

        r = sixteenbits + r;
    }
    return r;
};

string binary::intToBinary5B(string inteiro)
{

    string r;
    int n = stoi(inteiro);
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }

    string fivebits;

    if (r.size() < 5)
    {

        for (int i = r.size(); i < 5; i++)
        {
            fivebits = "0" + fivebits;
        }

        r = fivebits + r;
    }
    return r;
};

const vector<string> explode(const string &s, const char &c)
{
    if (s == "" || s.length() <= 0)
    {
        cout << "explode(): string vazia" << endl;
        return vector<string>();
    }

    string buff{""};
    vector<string> v;

    for (auto n : s)
    {
        if (n != c)
            buff += n;
        else if (n == c && buff != "")
        {
            v.push_back(buff);
            buff = "";
        }
    }
    if (buff != "")
        v.push_back(buff);

    return v;
}

string binary::Linha(string procurado, string command)
{

    int contador = 0;

    for (int i = 0; i < listaDeBinarios->size(); i++)
    {
        contador = contador + 4;
        string verify = listaDeBinarios->at(i);
        if (verify == command)
        {
            for (int j = i + 1; j < listaDeBinarios->size(); j++)
            {
                contador + 4;
                string FindCommando = listaDeBinarios->at(j);
                if (FindCommando.find(command))
                {
                    return to_string(contador);
                }
            }
        }
    }

    return "NotFound";
};

string binary::translateCommandToBinary(string &commandToTranslate)
{

    string regSource = "";
    string regTarget = "";
    string rd = "";
    string shamt = "";
    Registradores *reg = new Registradores();

    vector<string> lista = explode(commandToTranslate, ' ');

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
        rd = reg->mapeia(lista.at(1));
        ;
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
        opcode = "00000";
        shamt = intToBinary5B(lista.at(3));
        funct = "000000";
        regSource = "00000";
        regTarget = reg->mapeia(lista.at(2));
        rd = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "addi")
    {
        string finalString = typeIcommands(lista);
        reg->~Registradores();
        return finalString;
    }
    else if (lista.at(0) == "lw")
    {
        string finalString = typeIcommands(lista);
        reg->~Registradores();
        return finalString;
    }
    else if (lista.at(0) == "sw")
    {
        string finalString = typeIcommands(lista);
        reg->~Registradores();
        return finalString;
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
        opcode = "000000";
        shamt = "000000";
        funct = "001000";
        regTarget = "00000";
        rd = "00000";
        regSource = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "jal")
    {
        string finalString = typeJcommands(lista);
        reg->~Registradores();
        return finalString;
    }

    reg->~Registradores();
    listaDeBinarios->push_back(opcode + regSource + regTarget + rd + shamt + funct);
    return opcode + regSource + regTarget + rd + shamt + funct;
};

string binary::typeIcommands(vector<string> lista)
{

    string regSource = "";
    string regTarget = "";
    string offset = "";
    Registradores *reg = new Registradores();

    if (lista.at(0) == "addi")
    {
        opcode = "001000";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(1));
        offset = intToBinary16B(lista.at(3));
    }

    else if (lista.at(0) == "beq")
    {
        opcode = "000100";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(1));
        string endereco = Linha(lista.at(3), lista.at(0) + lista.at(1) + lista.at(2) + lista.at(3));
        if (endereco != "NotFound")
        {

            int end = stoi(endereco);
            int off =end / 4;// (PC::getPC() + 4 - end) / 4;
            offset = intToBinary16B(to_string(off));
        }
        else
        {

            return "ERRO";
        }
    }
    else if (lista.at(0) == "bne")
    {
        opcode = "000101";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(1));

        string endereco = Linha(lista.at(3), lista.at(0) + lista.at(1) + lista.at(2) + lista.at(3));
        if (endereco != "NotFound")
        {

            int end = stoi(endereco);
            int off = end /4 ;//(PC::getPC() + 4 - end) / 4;
            offset = intToBinary16B(to_string(off));
        }
        else
        {

            return "ERRO";
        }
    }
    else if (lista.at(0) == "sw")
    {
        opcode = "101011";
        regTarget = reg->mapeia(lista.at(1));
        vector<string> lista2 = explode(lista.at(2), '(');
        vector<string> lista3 = explode(lista2.at(1), ')');
        offset = intToBinary16B(lista2.at(0));
        regSource = reg->mapeia(lista3.at(0));
    }
    else if (lista.at(0) == "lw")
    {

        opcode = "100011";
        regTarget = reg->mapeia(lista.at(1));
        vector<string> lista2 = explode(lista.at(2), '(');
        vector<string> lista3 = explode(lista2.at(1), ')');
        offset = intToBinary16B(lista2.at(0));
        regSource = reg->mapeia(lista3.at(0));
    }

    listaDeBinarios->push_back(opcode + regSource + regTarget + offset);
    return opcode + regSource + regTarget + offset;
};

string binary::typeJcommands(vector<string> lista)
{

    string shamt = "";
    string rt = "";
    string rd = "";
    string rs = "";
    Registradores *reg = new Registradores();
    if (lista.at(0) == "j")
    {

        opcode = "000010";
    }
    else
    {
    }
    return "";
};

string binary::getFunct()
{

    return this->opcode;
};

string binary::getOP()
{

    return this->funct;
};

