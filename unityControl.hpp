#ifndef UNITYCONTROL_H
#define UNITYCONTROL_H

#include <iostream>
#include <string>

using namespace std;

class UnityControl
{       
    public:
        string PCWriteCond;
        string PCWrite;
        string IorD;
        string MemRead;
        string MemWrite;
        string MemReg;
        string IRWrite;
        string PCSource;
        string ALUOp;
        string ALUSrcB;
        string ALUSrcA;
        string RegWrite;
        string RegDst;
};

#endif 