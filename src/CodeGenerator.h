#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include "Scanner.h"
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <string>
#include <vector>

class CodeGenerator
{
public:
    struct Operand{
        wchar_t* _name;
        int _value;

        Operand() : _name(nullptr), _value(0){}
        Operand(wchar_t* name, int value) : _name(coco_string_create(name)), _value(value) { }
    };

    enum class Operation{
        ADD,
        SUB,
        ASSIGN
    };

private:
    const static std::wstring DataHeader;
    const static std::wstring AllocationKeyword;
    const static std::wstring IntegerSize;

    void generateOperation(Operand op1, Operand op2);

    std::vector<std::wstring> _registers;
    int _registerIndex;

    std::wstring reserveRegister();

    std::wstring returnRegister();

    void genAdd();


    void genSub();
public:
    CodeGenerator();

    std::wstring _data;

    std::wstring _text;

    void allocateInteger(const wchar_t* name);

    void genOperation(Operation op);

    void loadOperand(Operand& op);

    void storeOperand(Operand& op1, Operand& op2);

    void genAssign(wchar_t* name);

    void writeToFile();

    std::wstring lastReservedRegister();

    void insertExitCode();

    std::wstring lastAssignedVariable;
};


#endif 
