#you can change this to the name of your program:
COMPILER = ./Homework2

all:
		Coco src/Coco/HW2.atg -o src/
		g++ src/Parser.cpp src/CodeGenerator.cpp src/SymbolTable.cpp src/main.cpp src/Scanner.cpp -o $(COMPILER)
test:
			$(COMPILER) test.pas
			./source
			echo $?
