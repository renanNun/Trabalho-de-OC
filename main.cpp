#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "binary.h"
#include "Leitor.hpp"

std::fstream outputFile;

using namespace std;

int main(int argc, char *argv[])
{

    static vector<string> ListadeComandos;
    Leitor *leitor = new Leitor(argv[1]);
    ListadeComandos = leitor->getVector();

    outputFile.open(argv[2], ios::out); //Abre o Arquivo de Saida

    if (!outputFile)
    {
        cerr << "Erro ao Abrir o Arquivo de Saida! " << endl;
        exit(1);
    }

    binary *bin = new binary();

        for (int i = 0; i < ListadeComandos.size(); i++)
    {
        cout << ListadeComandos.at(i) << endl;
    }

    for (int i = 0; i < ListadeComandos.size(); i++)
    {
        string verify = bin->translateCommandToBinary(ListadeComandos.at(i)); 
        cout << verify << endl;
    }

    outputFile.close();

    return 0;
}