CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: nuvem

nuvem: nuvem.o tabela.o
	gcc $(CFLAGS) nuvem.o tabela.o -o nuvem $(LDFLAGS)

nuvem.o: nuvem.c
	gcc $(CFLAGS) -c nuvem.c

tabela.o: tabela.c
	gcc $(CFLAGS) -c tabela.c

clean:
	rm -f nuvem nuvem.o tabela.o
