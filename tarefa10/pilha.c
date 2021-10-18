#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"

Pilha criar_pilha(int capacidade) {
    Pilha pilha = {};
    
    pilha.v = malloc(capacidade * sizeof(Mercadoria));
    if (pilha.v == NULL) {
        exit(1);
    }

    pilha.capacidade = capacidade;
    pilha.topo = -1;

    return pilha;
}

int empilhar(Pilha *pilha, Mercadoria m) {
    if (pilha->topo >= pilha->capacidade - 1) {
        return 0;
    }

    pilha->topo++;
    strcpy(pilha->v[pilha->topo], m);

    return 1;
}

int desempilhar(Pilha *pilha) {
    if (pilha->topo < 0) {
        return 0;
    }

    pilha->topo--;

    return 1;
}