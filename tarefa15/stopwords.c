#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stopwords.h"

int particionamento_stopwords(char **vetor, int inicio, int fim) {
    int posicao_pivo = fim;

    int i = inicio;
    for (int j = inicio; j < fim; j ++) {
        if (strcmp(vetor[j], vetor[posicao_pivo]) < 0) {
            char aux[TAMANHO_PALAVRA];
            strcpy(aux, vetor[i]);
            strcpy(vetor[i], vetor[j]);
            strcpy(vetor[j], aux);

            i++;
        }
    }

    // Coloca o pivô no lugar dele
    if (i != posicao_pivo) {
        char aux[TAMANHO_PALAVRA];
        strcpy(aux, vetor[i]);
        strcpy(vetor[i], vetor[posicao_pivo]);
        strcpy(vetor[posicao_pivo], aux);

        posicao_pivo = i;
    }

    return posicao_pivo;
}

void quick_sort_stopwords(char **vetor, int inicio, int fim) {
    if (inicio < fim) {
        int posicao_pivo = particionamento_stopwords(vetor, inicio, fim);

        quick_sort_stopwords(vetor, inicio, posicao_pivo-1);
        quick_sort_stopwords(vetor, posicao_pivo+1, fim);
    }
}

int busca_binaria_stopwords(char **vetor, int inicio, int fim, char *valor) {
    if (inicio > fim) {
        return -1;
    }

    int idx = (inicio + fim) / 2;

    int comparacao = strcmp(valor, vetor[idx]);
    if (comparacao == 0) {
        return idx;
    } else if (comparacao < 0) {
        return busca_binaria_stopwords(vetor, 0, idx-1, valor);
    } else {
        return busca_binaria_stopwords(vetor, idx+1, fim, valor);
    }
}

void tratar_palavra(char *palavra) {
    int i = 0, j = 0;

    while (palavra[i] != '\0') {
        if (isalpha(palavra[i])) {
            palavra[j] = tolower(palavra[i]);
            j++;
        }
        i++;
    }

    palavra[j] = '\0';
}

char **ler_stopwords(int s) {
    char **stopwords = malloc(s * sizeof(char*));
    
    for (int i = 0; i < s; i++) {
        stopwords[i] = malloc(TAMANHO_PALAVRA * sizeof(char));
        scanf("%s", stopwords[i]);
    }

    quick_sort_stopwords(stopwords, 0, s-1);

    return stopwords;
}

void destruir_stopwords(char **stopwords, int s) {
    for (int i = 0; i < s; i++) {
        free(stopwords[i]);
    }

    free(stopwords);
}

int eh_stopword(char *palavra, char **stopwords, int s) {
    int idx = busca_binaria_stopwords(stopwords, 0, s-1, palavra);

    if (idx < 0) {
        return 0;
    } else {
        return 1;
    }
}
