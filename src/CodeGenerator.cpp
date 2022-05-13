#include "CodeGenerator.h"
#include <fstream>
#include <string>

const std::wstring CodeGenerator::DataHeader        = std::wstring(L".data\n");
const std::wstring CodeGenerator::AllocationKeyword = std::wstring(L".comm");
const std::wstring CodeGenerator::IntegerSize       = std::wstring(L"8");

CodeGenerator::CodeGenerator(){
    _text = std::wstring(L".text\n.globl _start\n\n_start:\n");
    _registers.push_back(std::wstring(L"%r8"));
    _registers.push_back(std::wstring(L"%r9"));
    _registers.push_back(std::wstring(L"%r10"));
    _registers.push_back(std::wstring(L"%r11"));
    _registers.push_back(std::wstring(L"%r12"));
    _registers.push_back(std::wstring(L"%r13"));
    _registers.push_back(std::wstring(L"%r14"));
    _registers.push_back(std::wstring(L"%r15"));
    
    _registerIndex = 0;
}

void CodeGenerator::allocateInteger(const wchar_t* name) {
    _data.append(AllocationKeyword + L" " + std::wstring(name) + L", " + IntegerSize + L"\n");
}


void CodeGenerator::genAdd(){
    std::wstring reg1 = returnRegister();
    std::wstring reg2 = lastReservedRegister();
    
    _text.append(L"add " + reg1 + L", " + reg2 + L"\n");
}

void CodeGenerator::genOperation(Operation op) {
    switch(op){
        case Operation::ADD : genAdd(); break;
        case Operation::SUB : genSub(); break;
    } 
}


void CodeGenerator::insertExitCode(){
    _text.append(L"mov $60, %rax\n");
    _text.append(L"mov " + lastAssignedVariable + L", %rdi\n");
    _text.append(L"syscall");
}

void CodeGenerator::genAssign(wchar_t* name){
    std::wstring reg = returnRegister();

    _text.append(L"movq " + reg + L", "  + name + L"\n");
}

void CodeGenerator::genSub(){
    std::wstring reg1 = returnRegister();
    std::wstring reg2 = lastReservedRegister();
    
    _text.append(L"sub " + reg1 + L", " + reg2 + L"\n");
}

std::wstring CodeGenerator::reserveRegister() {
    if(_registerIndex >= _registers.size() || _registerIndex < 0){
        int pix = 4;
        ++pix;
    }

    return _registers[_registerIndex++];
}

std::wstring CodeGenerator::returnRegister(){
    return _registers[--_registerIndex];
}

std::wstring CodeGenerator::lastReservedRegister(){
    return _registers[_registerIndex - 1];
}

void CodeGenerator::loadOperand(Operand& op) {
    std::wstring reg = reserveRegister();
    if(!std::wstring(op._name).empty()) //Is a variable 
    {
         _text.append(L"movq " + std::wstring(op._name) + L", " + reg + L"\n");
    }
    else{
        _text.append(L"movq " + std::wstring(L"$") + std::to_wstring(op._value) + L", " + reg + L"\n");
    }
}

void CodeGenerator::storeOperand(Operand& op1, Operand& op2){
    if(std::wstring(op2._name).empty()) //Is a variable 
    {
        std::wstring reg = reserveRegister();
         _text.append(L"movq " + reg + L", " + std::wstring(op1._name) + L"\n");
    }
    else{
        _text.append(L"movq " + std::wstring(L"$") + std::to_wstring(op2._value) + L" " + std::wstring(op1._name) + L"\n");
    }   
}

void CodeGenerator::generateOperation(Operand op1, Operand op2){
    bool isNumber = std::wstring(op2._name).empty();

    const std::wstring instruction(L"movq");
    if(isNumber) {
        _text.append(instruction + L"$" + std::to_wstring(op2._value) + L"," + std::to_wstring(op1._value) + L"\n");
    }
}

void CodeGenerator::writeToFile(){
    std::wofstream outputFile("source.s");

    outputFile << _data <<std::endl <<_text<<std::endl;
    outputFile.flush();
    outputFile.close();
}

