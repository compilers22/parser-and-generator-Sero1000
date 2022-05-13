#include "SymbolTable.h"
#include "Parser.h"
#include "Scanner.h"

SymbolTable::SymbolTable(Parser* parser) : globalScope(nullptr){

}

Obj::Obj(wchar_t* name, Type type) : _name(coco_string_create(name)), _type(type), _next(nullptr){

}

Obj* SymbolTable::NewObj(wchar_t* name, Obj::Type type){
    Obj* newObj = new Obj(name, type);
    if(globalScope == nullptr){
        globalScope = newObj;
        return newObj;
    }


    //Searching for a symbol with the same name
    Obj* current = globalScope;
    Obj* last = nullptr;

    while (current != nullptr) { 
    	if (coco_string_equal(current->_name, name)) Err(L"name declared twice");
    	last = current;
        current = current->_next; 
    }

    last->_next = newObj;
    
    return newObj;
}

Obj* SymbolTable::Find(wchar_t* name){
    Obj* current = globalScope;

    while(!coco_string_equal(current->_name,name)){
        current = current->_next;
    }

    return current;
}

void SymbolTable::Err(wchar_t* msg){
    errors->Error(0,0,msg);
}
