#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "fila.h"

No *criar_no(Navio n) {    
    Navio *navio = malloc(sizeof(Navio));
    if (navio == NULL) {
        exit(1);
    }
    
    strcpy(navio->nome, n.nome);
    strcpy(navio->objetivo, n.objetivo);
    strcpy(navio->tipo_mercadoria, n.tipo_mercadoria);
    navio->carga = n.carga;

    No *no = malloc(sizeof(No));
    if (no == NULL) {
        exit(1);
    }

    no->navio = navio;
    no->proximo = NULL;

    return no;
}

void destruir_no(No *no) {
    free(no->navio);
    free(no);
    
    return;
}

Fila criar_fila_navios() {
    Fila fila = {};
    fila.inicio = NULL;
    fila.fim = NULL;
    fila.qtd = 0;

    return fila;
}

void destruir_fila_navios(Fila fila) {
    No *no = fila.inicio;

    while (no != NULL) {
        No *prox = no->proximo;

        destruir_no(no);

        no = prox;
    }

    return;
}

Fila ler_fila_navios(int numero_navios) {
    Fila fila = criar_fila_navios();

    for (int i = 0; i < numero_navios; i++) {
        Navio navio = {};
        scanf("%s %s %s %d", navio.nome, navio.objetivo, navio.tipo_mercadoria, &navio.carga);

        enfileirar(&fila, navio);
    }

    return fila;
}

void enfileirar(Fila *fila, Navio navio) {
    No *no = criar_no(navio);

    if (fila->inicio == NULL) {
        fila->inicio = fila->fim = no;
    } else {
        fila->fim->proximo = no;
        fila->fim = no;
    }

    fila->qtd++;

    return;
}

Navio desenfileirar(Fila *fila) {
    No *no = fila->inicio;

    Navio navio = {};

    strcpy(navio.nome, no->navio->nome);
    strcpy(navio.objetivo, no->navio->objetivo);
    strcpy(navio.tipo_mercadoria, no->navio->tipo_mercadoria);
    navio.carga = no->navio->carga;
    
    if (fila->inicio == fila->fim) {
        fila->inicio = fila->fim = NULL;
    } else {
        fila->inicio = fila->inicio->proximo;
    }

    fila->qtd--;

    destruir_no(no);

    return navio;
}