CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: docas

docas: docas.o pilha.o fila.o
	gcc $(CFLAGS) docas.o pilha.o fila.o -o docas $(LDFLAGS)

docas.o: docas.c
	gcc $(CFLAGS) -c docas.c

pilha.o: pilha.c
	gcc $(CFLAGS) -c pilha.c

fila.o: fila.c
	gcc $(CFLAGS) -c fila.c

clean:
	rm -f docas docas.o pilha.o fila.o
