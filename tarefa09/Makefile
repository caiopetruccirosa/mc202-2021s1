CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: equipes

equipes: equipes.o lista.o
	gcc $(CFLAGS) equipes.o lista.o -o equipes $(LDFLAGS)

equipes.o: equipes.c
	gcc $(CFLAGS) -c equipes.c

lista.o: lista.c
	gcc $(CFLAGS) -c lista.c

clean:
	rm -f equipes equipes.o lista.o
