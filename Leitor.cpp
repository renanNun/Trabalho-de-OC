#include "Leitor.hpp"

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
        Leitor::ListadeComandos.push_back(line);
        line = "";
    }
};

vector<string> Leitor::getVector()
{

    return Leitor::ListadeComandos;
};