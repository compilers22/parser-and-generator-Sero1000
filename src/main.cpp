#include "CodeGenerator.h"
#include "Parser.h"
#include "Scanner.h"
#include "SymbolTable.h"
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <iostream>
#include <iterator>
#include <fstream>
#include <stdlib.h>


int main(int argc, char* argv[]){
    FILE* input_file = fopen(argv[1], "r");
    Scanner* scanner = new Scanner(input_file);
    Parser* parser = new Parser(scanner);
    parser->tab = new SymbolTable(parser);
    parser->gen = new CodeGenerator();

    parser->Parse();
    parser->gen->insertExitCode();
    parser->gen->writeToFile();

    system("as -o source.o source.s");
    system("ld -o source source.o");

    return 0;
}
