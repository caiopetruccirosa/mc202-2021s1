CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g

.PHONY: all clean

all: roteador

roteador: roteador.o filaprioridade.o
	gcc $(CFLAGS) roteador.o filaprioridade.o -o roteador $(LDFLAGS)

roteador.o: roteador.c
	gcc $(CFLAGS) -c roteador.c

filaprioridade.o: filaprioridade.c
	gcc $(CFLAGS) -c filaprioridade.c

clean:
	rm -f roteador roteador.o filaprioridade.o
