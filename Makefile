#M(m)akefile

CC = gcc
CFLAGS = -Wall -std=c99 -g


#   Sources
SOURCES = main.c table.c files.c 

#   Objects
OBJECTS = main.o table.o files.o 

wrdmttns: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c table.h files.h 

files.o: files.c files.h

table.o: table.c table.h files.h


FILES = $(shell ls ../test/*.dict)
FILES = $(shell ls ../test/*.pals)


VALG = valgrind --leak-check=full

t:
	for F in ${FILES}; do  ./wrdmttns $${F} ; done;

tv:
	for F in ${FILES}; do  $(VALG) ./wrdmttns $${F} ; done;
