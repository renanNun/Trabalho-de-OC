
#ifndef BINARY_H
#define BINARY_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "componentes/registradores.hpp"


using namespace std;

class binary
{
private:
   vector<string> *listaDeBinarios;
   static string opcode ;
   static string funct  ;

public:
   binary();
   ~binary();
   vector<string> * getLista();
   string translateCommandToBinary(string  &commandToTranslate);
   string intToBinary16B (string inteiro);
   string intToBinary5B (string inteiro);
   string typeIcommands(vector<string> lista );
   string typeJcommands(vector<string> lista );
   string getFunct();
   string getOP();
};

#endif // BINARY_H