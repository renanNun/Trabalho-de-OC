#include "../Headers/Leitor.hpp"

Leitor::Leitor(string Caminho)
{

    leString(Caminho);
    inputFile.close();
};

void Leitor::leString(string Caminho)
{

    inputFile.open(Caminho, ios::in);
    if (!inputFile)
    {
        cerr << "Erro ao Abrir o Arquivo de Entrada!" << endl;
        exit(1);
    }

    string line;

    while (getline(inputFile, line))
    {
        this->Leitor::getInstance().push_back(line);
        line = "";
    }
};

vector<string> Leitor::getVector()
{

    return this->Leitor::getInstance();
};

