CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: dns

dns: dns.o dominios.o usuarios.o
	gcc $(CFLAGS) dns.o dominios.o usuarios.o -o dns $(LDFLAGS)

dns.o: dns.c
	gcc $(CFLAGS) -c dns.c

dominios.o: dominios.c
	gcc $(CFLAGS) -c dominios.c

usuarios.o: usuarios.c
	gcc $(CFLAGS) -c usuarios.c

clean:
	rm -f dns dns.o dominios.o usuarios.o
