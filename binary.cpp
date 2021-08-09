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

commandTypes translateToCommand(int * binaryToTranslate){

   return add;
};

int translateToInt(int binaryToTranslatee){

 int num = binaryToTranslatee;
    int dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    int base = 1;
 
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
 
        dec_value += last_digit * base;
 
        base = base * 2;
    }
 
    return dec_value;


}
