#ifndef LEITOR_HPP
#define LEITOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
class Leitor
{

public:
    Leitor(string Caminho);
    vector<string> getVector();
    string Linha(string procurado, string command);
    vector<string> ListadeComandos;

    static vector<string> &getInstance()
    {
        static vector<string> ListadeComandos;

        return ListadeComandos;
    };

private:
    fstream inputFile;

    void leString(string Caminho);
};

#endif // LEITOR_HPP