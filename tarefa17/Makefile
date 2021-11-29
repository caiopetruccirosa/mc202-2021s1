CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: def_capitais

def_capitais: def_capitais.o grafo_cidades.o
	gcc $(CFLAGS) *.o -o def_capitais $(LDFLAGS)

def_capitais.o: def_capitais.c
	gcc $(CFLAGS) -c def_capitais.c

grafo_cidades.o: grafo_cidades.c
	gcc $(CFLAGS) -c grafo_cidades.c

clean:
	rm -f def_capitais *.o