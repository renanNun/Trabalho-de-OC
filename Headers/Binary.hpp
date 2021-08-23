
#ifndef BINARY_HPP
#define BINARY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Registrador.hpp"
#include "PC.hpp"
#include "Leitor.hpp"

using namespace std;

class Binary
{
private:
   vector<string> *listaDeBinarios;
   string opcode;
   string funct;
   string offset;
   string Linha(string procurado, string command);
   string intToBinary26B(string inteiro);
   string intToBinary16B(string inteiro);
   string intToBinary5B(string inteiro);
   string typeIcommands(vector<string> lista);
   string typeJcommands(vector<string> lista);
   string turnInTheSymmetrical(string number, int size);

public:
   Binary();
   ~Binary();
   vector<string> *getLista();
   string translateCommandToBinary(string &commandToTranslate);
   string getFunct();
   string getOP();
   string getoffset();
   
};

#endif // BINARY_HPP