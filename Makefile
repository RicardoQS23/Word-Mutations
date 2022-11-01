#M(m)akefile
CC = gcc
CFLAGS = -Wall -std=c99 -O3


#   Sources
SOURCES = main.c table.c files.c graph.c

#   Objects
OBJECTS = main.o table.o files.o graph.o

wrdmttns: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

main.o: main.c table.h files.h graph.h

files.o: files.c files.h

table.o: table.c table.h files.h 

graph.o: graph.c graph.h table.h


FILES = $(shell ls ..*.dict)
FILES = $(shell ls ..*.pals)


VALG = valgrind --leak-check=full --show-leak-kinds=all
clean:
	rm -rf *.o
valg:
	time ${VALG} ./wrdmttns portugues.dict mix_01.pals
r:
	./wrdmttns portugues.dict mix_01.pals
t:
	for F in ${FILES}; do  ./wrdmttns portugues.dict $${F}; done;

tv:
	for F in ${FILES}; do  $(VALG) ./wrdmttns portugues.dict $${F}; done;
