#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "processador.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::fstream inputFile;
std::fstream outputFile;

using namespace std;

int main(int argc, char *argv[])
{

    inputFile.open(argv[1], ios::in);   //Abre o Arquivo de Entrada
    outputFile.open(argv[2], ios::out); //Abre o Arquivo de Saida

    if (!inputFile)
    {
        cerr << "Erro ao Abrir o Arquivo de Entrada!" << endl;
        exit(1);
    }
     if (!outputFile)
    {
        cerr << "Erro ao Abrir o Arquivo de Saida! " << endl;
        exit(1);
    }

    string line;
    int cycle = 10;
    getline(inputFile,line);
    cout << line << endl;

    Processador* processor = new Processador();

    while(true)
    {
        processor->IF();
        Sleep(cycle);
        processor->ID();
        Sleep(cycle);
        processor->EX();
        Sleep(cycle);

        if(processor->getUnityControl()->getMemRead() == 1 
            || processor->getUnityControl()->getMemWrite() == 1
        ){
            processor->MEM();
            Sleep(cycle);
        }

        if(processor->getUnityControl()->getMemWrite() == 1)
        {
            processor->MR();
            Sleep(cycle);
        }
    }


    outputFile.close();
    inputFile.close();

    return 0;
}