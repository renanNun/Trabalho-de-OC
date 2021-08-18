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
        this->ListadeComandos.push_back(line);
        line = "";
    }
};

vector<string> Leitor::getVector()
{

    return this->ListadeComandos;
};

string Leitor::Linha(string procurado, string command)
{

    int contador = 0;

    for (int i = 0; i < ListadeComandos.size(); i++)
    {
        contador = contador + 4;
        string verify = ListadeComandos.at(i);
        if (verify == command)
        {
            for (int j = i + 1; j < ListadeComandos.size(); j++)
            {
                contador+4;
                string FindCommando = ListadeComandos.at(j);
                if(FindCommando.find(command)){
                    return to_string(contador);
                }
            }
        }
    }

    return "NotFound";
};