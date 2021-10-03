#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include "fila.h"

No *criar_no(Navio n) {    
    Navio *navio = malloc(sizeof(Navio));
    
    strcpy(navio->nome, n.nome);
    strcpy(navio->objetivo, n.objetivo);
    strcpy(navio->tipo_mercadoria, n.tipo_mercadoria);
    navio->carga = n.carga;

    No *no = malloc(sizeof(No));

    no->navio = navio;
    no->proximo = NULL;

    return no;
}

void destruir_no(No *no) {
    free(no->navio);
    free(no);
    
    return;
}

Fila *criar_fila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->inicio = NULL;
    fila->fim = NULL;

    return fila;
}

void destruir_fila(Fila *fila) {
    No *no = fila->inicio;

    while (no != NULL) {
        No *prox = no->proximo;

        destruir_no(no);

        no = prox;
    }

    free(fila);

    return;
}

Fila *ler_fila() {
    Fila *fila = criar_fila();

    return fila;
}

void imprimir_fila(Fila *fila) {
    // a implementar

    return;
}

void enfileirar(Fila *fila, Navio navio) {
    No *no = criar_no(navio);

    if (fila->inicio == NULL) {
        fila->inicio = fila->fim = no;
    } else {
        fila->fim->proximo = no;
        fila->fim = no;
    }

    return;
}

Navio desenfileirar(Fila *fila) {
    No *no = fila->inicio;

    Navio navio = {};

    strcpy(navio.nome, no->navio->nome);
    strcpy(navio.objetivo, no->navio->objetivo);
    strcpy(navio.tipo_mercadoria, no->navio->tipo_mercadoria);
    navio.carga = no->navio->carga;
    
    fila->inicio = fila->inicio->proximo;

    destruir_no(no);

    return navio;
}