# Type de compilation 
TYPE = gcc

# The name of the compiled file
OUTPUT = execute.exe

# Renvoie dans O_FILES tous les fichiers qui ont un pattern, se terminant par .o
O_FILES = $(wildcard *.o) 


# Affiche les options possible
first:		
	$(info Pour appliquer les autotests, entrer : make autotests)
	$(info Pour appliquer le test de la simulation global, entrer : make simu)
	$(info Pour appliquer le test de la communication usb, entrer : make usb)
	$(info Pour netoyer le dossier en supprimant les fichier .o et le execute.exe, entrer : make clean)


# Pour compiler et lancer le programme des autotests
autotests:
	gcc Src/consigne.c Src/autotests.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Src/main_test.c -o $(OUTPUT) -Wall
	./execute.exe
	make clean


# Pour compiler et lancer le programme du simulateur globale
simu:
	$(TYPE) -c Src/simulateur.c Src/consigne.c Src/autotests.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Src/test_sim.c -Wall 
	$(TYPE) autotests.o consigne.o test_sim.o regulation.o simulateur.o visualisationC.o visualisationT.o -o $(OUTPUT) -Wall
	./execute.exe
	make clean


# Pour compiler et lancer le programme du test de l'usb
usb:
	$(TYPE) -c Src/releve.c Src/commande.c Src/simulateur.c Src/usb.c Src/consigne.c Src/autotests.c Src/regulation.c Src/visualisationC.c Src/visualisationT.c Src/main.c -Wall 
	$(TYPE) autotests.o commande.o consigne.o main.o regulation.o releve.o simulateur.o usb.o visualisationC.o visualisationT.o Libraries/ftd2xx.lib -o execute -Wall
	./execute.exe
	make clean


# Permet de supprimer les fichiers se terminant par .o et le fichier execute.exe
clean:
	rm $(O_FILES)
	rm -f $(OUTPUT)