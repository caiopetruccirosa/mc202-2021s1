#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabela.h"

Tabela_Hash criar_tabela(int capacidade) {
    Tabela_Hash tabela;
    
    tabela.vetor = malloc(capacidade * sizeof(Contador*));
    if (tabela.vetor == NULL) {
        exit(1);
    }

    tabela.capacidade = capacidade;
    
    // inicializa o vetor
    for (int i = 0; i < tabela.capacidade; i++) {
        tabela.vetor[i] = NULL;
    }

    return tabela;
}

void destruir_tabela(Tabela_Hash tabela) {
    for (int i = 0; i < tabela.capacidade; i++) {
        free(tabela.vetor[i]);
    }

    free(tabela.vetor);
}

unsigned long int hash(char palavra[TAMANHO_PALAVRA]) {
    unsigned long int h = 41;

    for (int i = 0; i < strlen(palavra); i++) {
        h *= 13;
        h += palavra[i];
    }

    return h;
}

int buscar_contagem(Tabela_Hash tabela, char palavra[TAMANHO_PALAVRA]) {
    int idx = hash(palavra) % tabela.capacidade;

    Contador *contador = tabela.vetor[idx];
    while (contador != NULL && strcmp(palavra, contador->palavra) != 0) {
        if (strcmp(contador->palavra, palavra) == 0)
            return contador->contagem;
    }

    return 0;
}

void incrementar_contagem(Tabela_Hash *tabela, char palavra[TAMANHO_PALAVRA]) {    
    int idx = hash(palavra) % tabela->capacidade;

    Contador *no = tabela->vetor[idx];
    while (no != NULL) {
        if (strcmp(no->palavra, palavra) == 0) {
            no->contagem++;
            return;
        }

        no = no->proximo;
    }
    
    // colisão de hash, deve inserir no início da lista ligada
    Contador *novo = malloc(sizeof(Contador));

    strcpy(novo->palavra, palavra);
    novo->contagem = 1;


    tabela->vetor[idx] = novo;
}

void imprimir_tabela(Tabela_Hash tabela) {
    int soma = 0;

    for (int i = 0; i < tabela.capacidade; i++) {
        Contador *contador = tabela.vetor[i];

        if (contador != NULL) {
            soma += contador->contagem;

            printf("[Índice %d] -------\n", i);
            printf("[%s] --> %d, ", contador->palavra, contador->contagem);
            printf("\n-----------------------\n");
        }
    }

    printf("\nSoma das contagens na tabela : %d\n", soma);
}