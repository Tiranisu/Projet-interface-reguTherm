# How to compile the file
TYPE = gcc

# The name of the compiled file
OUTPUT = execute

#Look for all the files in the folder Src which and with .c
#C_FILES = $(wildcard Src/*.c)
O_FILES = $(wildcard *.o)
#$(TYPE) $(C_FILES) -o $(wildcard $(C_FILES).o) -Wall
all:		
	
	$(TYPE) -c Src/consigne.c -Wall
	$(TYPE) -c Src/regulation.c -Wall
	$(TYPE) -c Src/visualisationC.c -Wall
	$(TYPE) -c Src/visualisationT.c -Wall
	$(TYPE) $(O_FILES) -o execute -Wall

simu:
	$(TYPE) -c Inc/define.h Inc/simulateur.h Src/simulateur.c -Wall
	$(TYPE) -c Src/test_simulateur.c -Wall
	$(TYPE) simulateur.o test_simulateur.o -o execute -Wall


autotests:
	$(TYPE) Src/consigne.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Inc/autotests.h Src/autotests.c -Wall
	$(TYPE) autotests.o -o execute -Wall


clean:
	rm $(O_FILES)

