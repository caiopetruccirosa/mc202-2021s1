#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilha.h"

Pilha criar_pilha(int capacidade) {
    Pilha pilha = {};
    
    pilha.v = malloc(capacidade * sizeof(Conteiner));
    pilha.capacidade = capacidade;
    pilha.topo = -1;

    return pilha;
}

void empilhar(Pilha *pilha, Conteiner c) {
    pilha->topo++;
    pilha->v[pilha->topo] = c;

    return;
}

Conteiner desempilhar(Pilha *pilha) {
    Conteiner c = pilha->v[pilha->topo];
    pilha->topo--;

    return c;
}

int eh_pilha_cheia(Pilha pilha) {
    return pilha.topo >= pilha.capacidade;
}

int eh_pilha_vazia(Pilha pilha) {
    return pilha.topo < 0;
}

void imprimir_pilha(Pilha pilha) {
    for (int i = 0; i <= pilha.topo; i++) {
        printf("pilha, posição %d, conteiner com valor: %s\n", i, pilha.v[i].tipo_mercadoria);
    }

    return;
}

int pode_carregar(Pilha pilha, char tipo_mercadoria[]) {
    Conteiner c = pilha.v[pilha.topo];

    if (strcmp(c.tipo_mercadoria, tipo_mercadoria) == 0) {
        return 1;
    }

    return 0;
}