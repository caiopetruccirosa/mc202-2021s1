CFLAGS = -std=c99 -Wall -Werror -Werror=vla -g
LDFLAGS = -lm

.PHONY: all clean

all: dns

dns: dns.o dominios.o
	gcc $(CFLAGS) dns.o dominios.o -o dns $(LDFLAGS)

dns.o: dns.c
	gcc $(CFLAGS) -c dns.c

dominios.o: dominios.c
	gcc $(CFLAGS) -c dominios.c

test-example: dns
	./dns < testes/example.in

test-all: dns
	python3 testar.py

clean:
	rm -f dns dns.o dominios.o
