#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "binary.hpp"
#include "Leitor.hpp"
#include "processador.hpp"

std::fstream outputFile;

using namespace std;

int main(int argc, char *argv[])
{

    string caminho = argv[1];
    static vector<string> ListadeComandos;
    Leitor *leitor = new Leitor(caminho);
    ListadeComandos = leitor->getVector();

    outputFile.open(argv[2], ios::out); //Abre o Arquivo de Saida

    if (!outputFile)
    {
        cerr << "Erro ao Abrir o Arquivo de Saida! " << endl;
        exit(1);
    }

    Processador* processor = new Processador(ListadeComandos);
    processor->IF();
    Sleep(600);
    processor->ID();
    Sleep(600);
    processor->EX();
    Sleep(600);
    processor->MEM();
    Sleep(600);
    processor->WR();
    
    /*while(true)
    {
        processor->IF();
        Sleep(cycle);
        processor->ID();
        Sleep(cycle);
        processor->EX();
        Sleep(cycle);

        if(processor->getUnityControlMemRead() == 1 
            || processor->getUnityControlMemWrite() == 1
        ){
            processor->MEM();
            Sleep(cycle);
        }

        if(processor->getUnityControlMemWrite() == 1)
        {
            processor->MR();
            Sleep(cycle);
        }
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
    }*/

    outputFile.close();

    return 0;
}