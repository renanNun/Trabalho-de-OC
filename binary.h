
#ifndef BINARY_H
#define BINARY_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "commandTypes.h"

using namespace std;

class binary
{
private:
   vector<int> *listaDeBinarios;

public:
   binary(string arquivo);
   ~binary();
   commandTypes translateToCommand(int *binaryToTranslate);
   vector<int> * getLista();
   int translateToInt(int binaryToTranslatee);
};

#endif // BINARY_H