
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
   vector<int>* listaDeBinarios ; 

public:
     binary(string arquivo);
    ~binary();
    int translate(int binaryToTranslate);
    vector<int> * getLista();
};

#endif // BINARY_H