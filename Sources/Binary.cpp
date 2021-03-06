#include "../Headers/Binary.hpp"

string split(int inicio, int fim, string line)
{
    string aux;
    for (int i = inicio; i <= fim; i++)
        aux += line[i];

    return aux;
};

Binary::Binary()
{

    listaDeBinarios = new vector<string>();
    opcode = "";
    funct = "";
    offset = "";
};

Binary::~Binary()
{
    listaDeBinarios->~vector();
    delete[] this->listaDeBinarios;
};

vector<string> *Binary::getLista()
{

    return this->listaDeBinarios;
};

string Binary::intToBinary26B(string inteiro)
{

    string r;
    int n = stoi(inteiro);
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }

    string twentysixbits;

    if (r.size() < 26)
    {

        for (int i = r.size(); i < 26; i++)
        {
            twentysixbits = "0" + twentysixbits;
        }

        r = twentysixbits + r;
    }
    return r;
};

string Binary::intToBinary16B(string inteiro)
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

string Binary::intToBinary5B(string inteiro)
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

string Binary::Linha(string procurado)
{

    int contador = 0;
    for (int i = 0; i < Leitor::getInstance().size(); i++)
    {

        string verify = Leitor::getInstance().at(i);
        if (verify == procurado)
        {

            return to_string(contador + 1);
        }
        contador += 1;
    }
    contador = contador + 1;

    return "NotFound";
};

string Binary::translateCommandToBinary(string &commandToTranslate)
{

    string regSource = "";
    string regTarget = "";
    string rd = "";
    string shamt = "";
    Registrador *reg = new Registrador();

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
        funct = "100100";
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
        opcode = "000000";
        shamt = "00000";
        funct = "101010";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(3));
        rd = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "sll")
    {
        opcode = "000000";
        shamt = intToBinary5B(lista.at(3));
        funct = "000000";
        regSource = reg->mapeia(lista.at(2));
        regTarget = "00000";
        rd = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "addi")
    {
        string finalString = typeIcommands(lista);
        reg->~Registrador();
        return finalString;
    }
    else if (lista.at(0) == "lw")
    {
        string finalString = typeIcommands(lista);
        reg->~Registrador();
        return finalString;
    }
    else if (lista.at(0) == "sw")
    {
        string finalString = typeIcommands(lista);
        reg->~Registrador();
        return finalString;
    }
    else if (lista.at(0) == "beq")
    {
        string finalString = typeIcommands(lista);
        reg->~Registrador();
        return finalString;
    }
    else if (lista.at(0) == "bne")
    {
        string finalString = typeIcommands(lista);
        reg->~Registrador();
        return finalString;
    }
    else if (lista.at(0) == "j")
    {
        string finalString = typeJcommands(lista);
        reg->~Registrador();
        return finalString;
    }
    else if (lista.at(0) == "jr")
    {
        opcode = "000000";
        shamt = "00000";
        funct = "001000";
        regTarget = "00000";
        rd = "00000";
        regSource = reg->mapeia(lista.at(1));
    }
    else if (lista.at(0) == "jal")
    {
        string finalString = typeJcommands(lista);
        reg->~Registrador();
        return finalString;
    }
    else
    {

        return "11111111111111111111111111111111";
    }

    reg->~Registrador();
    // listaDeBinarios->push_back(opcode + regSource + regTarget + rd + shamt + funct);
    return opcode + regSource + regTarget + rd + shamt + funct;
};

string Binary::typeIcommands(vector<string> lista)
{
    if(lista.size()<3){

        cout<< "O comando est?? escrito de forma incorreta, favor arrumar e iniciar o programa novamente"<<endl;
        exit(-5);
    }

    string regSource = "";
    string regTarget = "";
    Registrador *reg = new Registrador();

    if (lista.at(0) == "addi")
    {
        opcode = "001000";
        regSource = reg->mapeia(lista.at(2));
        regTarget = reg->mapeia(lista.at(1));
        if (!lista.at(3).find("-"))
        {

            lista.at(3) = lista.at(3).substr(1, sizeof(lista.at(3)));
            offset = intToBinary16B(lista.at(3));
            offset = turnInTheSymmetrical(offset, 16);
        }

        else
        {
            offset = intToBinary16B(lista.at(3));
        }
    }

    else if (lista.at(0) == "beq")
    {
        opcode = "000100";
        regSource = reg->mapeia(lista.at(1));
        regTarget = reg->mapeia(lista.at(2));
        string endereco = Linha(lista.at(3) + ":");
        if (endereco != "NotFound")
        {
            int end = stoi(endereco);
            int off = (end - PC::getInstance().getPC() + 4) / 4;
            if (off < 0)
            {
                offset = intToBinary16B(to_string(off));
                offset = turnInTheSymmetrical(offset, 16);
            }
            else
            {
                offset = intToBinary16B(to_string(off));
            }
        }
        else
        {
            cout << "\nN??o foi possivel encontrar a estrutura\n";
            exit(-1);
        }
    }
    else if (lista.at(0) == "bne")
    {

        opcode = "000101";
        regSource = reg->mapeia(lista.at(1));
        regTarget = reg->mapeia(lista.at(2));
        string endereco = Linha(lista.at(3) + ":");
        if (endereco != "NotFound")
        {
            int end = stoi(endereco);
            int off = (end - PC::getInstance().getPC() + 4) / 4;
            if (off < 0)
            {
                offset = intToBinary16B(to_string(off));
                offset = turnInTheSymmetrical(offset, 16);
            }
            else
            {
                offset = intToBinary16B(to_string(off));
            }
        }
        else
        {
            cout << "\nN??o foi possivel encontrar a estrutura\n";
            exit(-1);
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

    // listaDeBinarios->push_back(opcode + regSource + regTarget + offset);
    return opcode + regSource + regTarget + offset;
};

string Binary::typeJcommands(vector<string> lista)
{

    if (lista.at(0) == "j")
    {

        opcode = "000010";
        string endereco = Linha(lista.at(1) + ":");
 
        if (endereco != "NotFound")
        {
            int end = stoi(endereco);
            int off = (end);

            if (off<0)
            {
                offset = intToBinary26B(to_string(off));
                offset = turnInTheSymmetrical(to_string(off), 26);
            }

            offset = intToBinary26B(to_string(off));
        }
        else
        {
            cout << "\nN??o foi possivel encontrar a estrutura\n";
            exit(-2);
        }
    }
    else
    {
        opcode = "000011";
        string endereco = Linha(lista.at(1) + ":");
        if (endereco != "NotFound")
        {
            int end = stoi(endereco);
            int off = (end);
            if (off<0)
            {
                offset = intToBinary26B(to_string(off));
                offset = turnInTheSymmetrical(to_string(off), 26);
            }

            offset = intToBinary26B(to_string(off));
        }
        else
        {
            cout << "\nN??o foi possivel encontrar a estrutura\n";
            exit(-2);
        }
    }
    return opcode + offset;
};

string Binary::getFunct()
{

    return this->funct;
};

string Binary::getOP()
{

    return this->opcode;
};
string Binary::getoffset()
{

    return this->offset;
};

string Binary::turnInTheSymmetrical(string number, int size)
{
    int first1Index = size - 1;
    while (number[first1Index] != '1')
    {
        first1Index--;
    }
    for (int i = first1Index - 1; i >= 0; i--)
    {
        number[i] = (number[i] == '0') ? '1' : '0';
    }
    return number;
}