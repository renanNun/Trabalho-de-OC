#ifndef PROCESSADOR_H
#define PROCESSADOR_H

#include <iostream>
#include <string>
#include <vector>

#include "PC.hpp"
#include "unityControl.hpp"
#include "ALU.hpp"
#include "binary.hpp"

using namespace std;

class Processador
{
    private:
        ALU* alu;
        UnityControl uc;

        vector<string> instructions;

        string Mux(string entrada0, string entrada1, string opcode);

        void controlSignals();

    public:
        Processador(vector<string> &instructions)
        {
            this->instructions = instructions;
        };
        ~Processador(){};

        void IF(){
            // Exibição do valor de PC atual
            cout <<"\nPC:\n" << "\tValor de PC: " << PC::getInstance().getPC() << endl;

            binary bin();
           
            cout << "Comando traduzido: " << bin.translateCommandToBinary(vector[0]);
            //cout << "Tamanho do vector " << this->instructions.size() << endl;

            //translateCommandToBinary(string &commandToTranslate);
            PC::getInstance().incremetPC();
        };


        string getUnityControlMemWrite(){return this->uc.MemWrite;};
        string getUnityControlMemRead(){return this->uc.MemRead;};
};



#endif // PROCESSADOR_H