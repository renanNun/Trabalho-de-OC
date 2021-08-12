#ifndef ALU_HPP
#define ALU_HPP
#include <iostream>
#include <string>

using namespace std;

class ALU
{

private:
    const string ZERO = "00000000000000000000000000000000";
    bool zero = true;
    bool overflow = false;
    int maxBits;
    string aluResult = ZERO;

    void addOperation(string a, string b)
    {
        bool carry = false;
        for (int i = this->maxBits - 1; i >= 0; i--)
        {
            if (a[i] == '0' && b[i] == '0')
            {
                if (carry)
                {
                    aluResult[i] = '1';
                    carry = false;
                }
                else
                {
                    aluResult[i] = '0';
                }
            }
            else if (a[i] == '1' && b[i] == '1')
            {
                if (carry)
                {
                    aluResult[i] = '1';
                }
                else
                {
                    aluResult[i] = '0';
                    carry = true;
                }
            }
            else
            {
                if (carry)
                {
                    aluResult[i] = '0';
                }
                else
                {
                    aluResult[i] = '1';
                }
            }
        }
        overflow = carry;
    }

    string turnInTheSymmetrical(string number)
    {
        int first1Index = this->maxBits - 1;
        while (number[first1Index] != '1')
        {
            first1Index--;
        }
        for (int i = first1Index - 1; i >= 0; i--)
        {
            number[i] = (number[i] == '0') ? '1' : '0';
        }
        return number;
    }

    void subOperation(string a, string b)
    {
        addOperation(a, turnInTheSymmetrical(b));
    }

    void andOperation(string a, string b)
    {
        for (int i = this->maxBits - 1; i >= 0; i--)
        {
            if (a[i] == '1' && b[i] == '1')
            {
                aluResult[i] = '1';
            }
            else
            {
                aluResult[i] = '0';
            }
        }
    }

    void orOperation(string a, string b)
    {
        for (int i = this->maxBits - 1; i >= 0; i--)
        {
            if (a[i] == '1' || b[i] == '1')
            {
                aluResult[i] = '1';
            }
            else
            {
                aluResult[i] = '0';
            }
        }
    }

    void setOnLessThan(string a, string b)
    {
        if (a[0] == '0' && b[0] == '1')
        {
            aluResult = ZERO;
        }
        else if (a[0] == '1' && b[0] == '0')
        {
            aluResult = "11111111111111111111111111111111";
        }
        else
        {
            subOperation(a, b);
            if (aluResult[0] == '1')
            {
                aluResult = "11111111111111111111111111111111";
            }
            else
            {
                aluResult = ZERO;
            }
        }
    }

    void shiftLeftLogical(string a, string b)
    {
        int shiftAmount = stoi(b, 0, 2);
        cout << shiftAmount << endl;
        for (int i = this->maxBits; i >= 0; i--)
        {
            aluResult[i] = a[(i + shiftAmount) % maxBits];
        }
    }

public:
    enum ALUOp
    {
        ADD,
        SUB,
        AND,
        OR,
        SLT,
        SLL,
    };

    ALU(int maxBits) { this->maxBits = maxBits; };
    ~ALU(){};
    bool getZeroSignal() { return zero; };
    string getALUResult() { return aluResult; };
    void makeOperation(string a, string b, ALUOp op)
    {
        switch (op)
        {
        case ALUOp::ADD:
        {
            addOperation(a, b);
            break;
        }
        case ALUOp::SUB:
        {
            subOperation(a, b);
            break;
        }
        case ALUOp::AND:
        {
            andOperation(a, b);
            break;
        }
        case ALUOp::OR:
        {
            orOperation(a, b);
            break;
        }
        case ALUOp::SLT:
        {
            setOnLessThan(a, b);
            break;
        }
        case ALUOp::SLL:
        {
            shiftLeftLogical(a, b);
            break;
        }
        }
        if (aluResult == ZERO)
        {
            zero = true;
        }
        else
        {
            zero = false;
        }
    };
};
#endif