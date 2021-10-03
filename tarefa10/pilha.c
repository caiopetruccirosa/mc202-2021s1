#include <stdlib.h>
#include "pilha.h"

Pilha criar_pilha(int capacidade) {
    Pilha pilha = {};
    
    pilha.v = malloc(capacidade * sizeof(Conteiner));
    pilha.capacidade = capacidade;
    pilha.topo = 0;

    return pilha;
}

void empilhar(Pilha *pilha, Conteiner conteiner) {
    pilha->v[++(pilha->topo)] = conteiner;
    return;
}

Conteiner desempilhar(Pilha *pilha) {
    return pilha->v[pilha->topo--];
}