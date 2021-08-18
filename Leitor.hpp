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

private:
    fstream inputFile;
    vector<string>  ListadeComandos;
    void leString(string Caminho);
};

#endif // LEITOR_HPP