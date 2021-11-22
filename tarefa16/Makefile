CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: rpg

rpg: rpg.o fila.o
	gcc $(CFLAGS) rpg.o fila.o -o rpg $(LDFLAGS)

rpg.o: rpg.c
	gcc $(CFLAGS) -c rpg.c

fila.o: fila.c
	gcc $(CFLAGS) -c fila.c

clean:
	rm -f rpg rpg.o fila.o
