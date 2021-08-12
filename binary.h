
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

public:
   binary();
   ~binary();
   vector<string> * getLista();
   string translateCommandToBinary(string  &commandToTranslate);
   string intToBinary (string inteiro);
   string typeRcommands(vector<string> *lista );
   string typeIcommands(vector<string> *lista );
   string typeJcommands(vector<string> *lista );
};

#endif // BINARY_H