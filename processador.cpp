#include "processador.hpp"

void Processador::IF()
{
    // Exibição do valor de PC atual
    cout <<"\nPC:\n" << "\tValor de PC: " << PC::getInstance().getPC() << endl;

    cout << "Tamanho do vector " << this->instructions.size() << endl;

    //translateCommandToBinary(string &commandToTranslate);
    PC::getInstance().incremetPC();
}