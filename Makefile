# How to compile the file
TYPE = gcc 

# The name of the compiled file
OUTPUT = execute

#Look for all the files in the folder Src which and with .c
C_FILES = $(wildcard Src/*.c)
# O_FILES = $(wildcard Src/*.o)

all:		
	$(TYPE) $(C_FILES) -o $(C_FILES).o -Wall


clean:
	rm $(OUTPUT).exe