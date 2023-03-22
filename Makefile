# How to compile the file
TYPE = gcc

# The name of the compiled file
OUTPUT = execute.exe

O_FILES = $(wildcard *.o)

all:		
	$(info Je suis papa)

simu:
	$(TYPE) -c Inc/define.h Inc/simulateur.h Src/simulateur.c -Wall
	$(TYPE) -c Src/test_simulateur.c -Wall
	$(TYPE) simulateur.o test_simulateur.o -o execute -Wall
	./execute.exe
	make clean


autotests:
	gcc Src/consigne.c Src/autotests.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Src/main.c -o $(OUTPUT) -Wall
	./execute.exe
	make clean


autotests-linux:
	gcc Src/consigne.c Src/autotests.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Src/main.c -o $(OUTPUT) -Wall
	./execute
	make clean


clean:
	rm $(O_FILES)
	rm execute.exe

test:
