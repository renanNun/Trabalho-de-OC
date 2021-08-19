
#ifndef BINARY_HPP
#define BINARY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "registradores.hpp"
#include "PC.hpp"
#include "Leitor.hpp"

using namespace std;

class binary
{
private:
   vector<string> *listaDeBinarios;
   string opcode;
   string funct;
   string Linha(string procurado, string command);
   string intToBinary26B(string inteiro);
   string intToBinary16B(string inteiro);
   string intToBinary5B(string inteiro);
   string typeIcommands(vector<string> lista);
   string typeJcommands(vector<string> lista);


public:
   binary();
   ~binary();
   vector<string> *getLista();
   string translateCommandToBinary(string &commandToTranslate);
   string getFunct();
   string getOP();
};

#endif // BINARY_HPP