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
        string Jump;
        string Branch;
        string MemRead;
        string MemWrite;
        string MemtoReg;
        string IRWrite;
        string ALUOp;
        string ALUSrc;
        string RegWrite;
        string RegDst;
};

#endif 