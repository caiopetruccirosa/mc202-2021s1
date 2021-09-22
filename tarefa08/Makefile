CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: boate

boate: boate.o fila.o
	gcc $(CFLAGS) boate.o fila.o -o boate $(LDFLAGS)

boate.o: boate.c
	gcc $(CFLAGS) -c boate.c

fila.o: fila.c
	gcc $(CFLAGS) -c fila.c

clean:
	rm -f boate boate.o fila.o
