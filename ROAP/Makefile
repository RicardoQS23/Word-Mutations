#make file example

CC = gcc #compiler

# flags para compilar
CFLAGS= -Wall -std=c99 -g
TARGET= roap
# gerar variáveis com listas ficheiros de cada tipo para usar nas várias regras
SRCS=$(wildcard *.c)
OBJS=$(patsubst %.c, %.o, $(SRCS))
HEADERS=$(wildcard *.h)
MAKEFILE=$(wildcard *.makefile) 
all: 
	$(CC)$(CFLAGS) main.c Intermedio.c Read.c Final.c Djikstra.c -o roap

# para criar um tar.gz com todos os ficheiros, dar o comando "make tgz"
tgz: $(TARGET).tar.gz

$(TARGET).tar.gz: $(SRCS) $(HEADERS) $(MAKEFILE)
	tar czvf $@ $^

clean: 
	rm $(TARGET)
