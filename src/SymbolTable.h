#ifndef SYMBOL_TABLE_Y
#define SYMBOL_TABLE_Y


class Parser;
class Errors;
struct Obj{
    enum class Type{
        Integer,
        String
    };

    Obj(wchar_t* name, Type type);
    Type _type;
    wchar_t* _name;
    Obj* _next;
};


class SymbolTable {
public:
    SymbolTable(Parser* parser);
    void Err(wchar_t* msg);

    Obj* NewObj(wchar_t* name, Obj::Type type);

    Obj* Find(wchar_t* name);
private:
    Obj* globalScope;

    Errors* errors;
};

#endif
