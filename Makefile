# How to compile the file
TYPE = gcc

# The name of the compiled file
OUTPUT = execute.exe

O_FILES = $(wildcard *.o)

first:		
	$(info Pour appliquer les autotests, entrer : make autotests)
	$(info Pour appliquer le test de la simulation global, entrer : make simu)
	$(info Pour appliquer le test de la communication usb, entrer : make usb)


autotests:
	gcc Src/consigne.c Src/autotests.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Src/main_test.c -o $(OUTPUT) -Wall
	./execute.exe


simu:
	$(TYPE) -c Src/simulateur.c Src/consigne.c Src/autotests.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Src/test_sim.c -Wall 
	$(TYPE) autotests.o consigne.o test_sim.o regulation.o simulateur.o visualisationC.o visualisationT.o -o $(OUTPUT) -Wall
	./execute.exe


usb:
	$(TYPE) -c Src/releve.c Src/commande.c Src/simulateur.c Src/usb.c Src/consigne.c Src/autotests.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Src/main.c -Wall 
	$(TYPE) autotests.o commande.o consigne.o main.o regulation.o releve.o simulateur.o usb.o visualisationC.o visualisationT.o ftd2xx.lib -o execute -Wall
	./execute.exe


clean:
	rm $(O_FILES)
	rm -f execute.exe