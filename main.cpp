#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "binary.h"

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
   

    // cout << "\t\t\tTrabalho de Orrganização de computadores" << endl;
    // cout << "Alunos: Luan Reis Ciribelli e Renan Nunes da Costa Gonçalves, João Pedro Lima" << endl;
    // cout << "Nome do arquivo: " << argv[1] << endl;

    // outputFile << "\t\t\tTTrabalho de Orrganização de computadores" << endl;
    // outputFile << "Alunos: Luan Reis Ciribelli e Renan Nunes da Costa Gonçalves, João Pedro Lima" << endl;
    // outputFile << "Nome do arquivo: " << argv[1] << endl;

    string line;

   getline(inputFile,line);
    cout << line << endl;

    binary* bin = new binary();
    cout << "Instancia" << endl;
    string verify = bin->translateCommandToBinary(line);
    cout << verify << endl;

    outputFile.close();
    inputFile.close();

    return 0;
}