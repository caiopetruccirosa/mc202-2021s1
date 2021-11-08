#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tabela.h"

int particionamento_contador(Contador *vetor, int inicio, int fim) {
    int posicao_pivo = fim;

    int i = inicio;
    for (int j = inicio; j < fim; j ++) {
        if ((vetor[j].contagem > vetor[posicao_pivo].contagem) ||
            (vetor[j].contagem == vetor[posicao_pivo].contagem && strcmp(vetor[j].palavra, vetor[posicao_pivo].palavra) < 0)) {
            Contador aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;

            i++;
        }
    }

    // Coloca o pivô no lugar dele
    if (i != posicao_pivo) {
        Contador aux = vetor[i];
        vetor[i] = vetor[posicao_pivo];
        vetor[posicao_pivo] = aux;

        posicao_pivo = i;
    }

    return posicao_pivo;
}

void quick_sort_contador(Contador *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int posicao_pivo = particionamento_contador(vetor, inicio, fim);

        quick_sort_contador(vetor, inicio, posicao_pivo-1);
        quick_sort_contador(vetor, posicao_pivo+1, fim);
    }
}

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

unsigned int long hash(char *palavra) {
    int h = 41;

    for (int i = 0; i < strlen(palavra); i++) {
        h *= 13;
        h += palavra[i];
    }

    return h;
}

int incrementar_contagem(Tabela_Hash *tabela, char palavra[TAMANHO_PALAVRA]) {    
    unsigned int long h = hash(palavra);

    for (int i = 0; i < tabela->capacidade; i++) {
        int idx = (i + h) % tabela->capacidade;

        if (tabela->vetor[idx] == NULL) {
            // contador da palavra não foi inserido na tabela hash ainda
            Contador *cont = malloc(sizeof(Contador));
            
            strcpy(cont->palavra, palavra);
            cont->contagem = 1;
            
            tabela->vetor[idx] = cont;

            return 1;
        } else if (tabela->vetor[idx] != NULL && strcmp(palavra, tabela->vetor[idx]->palavra) == 0) {
            tabela->vetor[idx]->contagem++;

            return 1;
        }
    }

    // caso não tenha sido possível incrementar a contagem
    return 0;
}

Contador *palavras_mais_frequentes(Tabela_Hash tabela) {
    Contador *ordenado = malloc(tabela.capacidade * sizeof(Contador));

    int tamanho = 0;
    for (int i = 0; i < tabela.capacidade; i++) {
        if (tabela.vetor[i] != NULL) {
            ordenado[tamanho] = *tabela.vetor[i];
            tamanho++;
        }
    }

    quick_sort_contador(ordenado, 0, tamanho-1);

    Contador *mais_frequentes = malloc(QTD_PALAVRAS_MAIS_FREQUENTES * sizeof(Contador));
    for (int i = 0; i < QTD_PALAVRAS_MAIS_FREQUENTES && tamanho; i++) {
        mais_frequentes[i] = ordenado[i];
    }

    free(ordenado);

    return mais_frequentes;
}

void imprimir_palavras_mais_frequentes(Tabela_Hash tabela) {
    Contador *mais_frequentes = palavras_mais_frequentes(tabela);

    for (int i = 0; i < QTD_PALAVRAS_MAIS_FREQUENTES; i++) {
        printf("%s %d\n", mais_frequentes[i].palavra, mais_frequentes[i].contagem);
    }

    free(mais_frequentes);
}