#include "binary.h"

binary::binary(string arquivo)
{
    listaDeBinarios = new vector<int>();
    string aux;
    int aux2;

    for (int i = 0; i < arquivo.size(); i=i+9)
    {
        aux= arquivo.substr(i,i+8);
        aux2= stoi(aux);
        listaDeBinarios->push_back(aux2);
    }
        
};

binary::~binary()
{
    listaDeBinarios->~vector();
    delete[] this->listaDeBinarios;
};

vector<int> * binary::getLista()
{

    return this->listaDeBinarios;
};

commandTypes translate(int * binaryToTranslate){

   
};

