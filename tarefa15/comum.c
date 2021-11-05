#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "tabela.h"
#include "comum.h"

int particionamento(char **vetor, int inicio, int fim) {
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

void quick_sort(char **vetor, int inicio, int fim) {
    if (inicio < fim) {
        int posicao_pivo = particionamento(vetor, inicio, fim);

        quick_sort(vetor, inicio, posicao_pivo-1);
        quick_sort(vetor, posicao_pivo+1, fim);
    }
}

int busca_binaria(char **vetor, int inicio, int fim, char *valor) {
    if (inicio > fim) {
        return -1;
    }

    int idx = (inicio + fim) / 2;

    int comparacao = strcmp(valor, vetor[idx]);
    if (comparacao == 0) {
        return idx;
    } else if (comparacao < 0) {
        return busca_binaria(vetor, 0, idx-1, valor);
    } else {
        return busca_binaria(vetor, idx+1, fim, valor);
    }
}

void filtrar_nao_alphanumericos(char *palavra) {
    int i = 0, j = 0;

    while (palavra[i] != '\0') {
        if (isalnum(palavra[i])) {
            palavra[j] = palavra[i];
            j++;
        }
        i++;
    }

    palavra[j] = '\0';
}

char **palavras_mais_frequentes(Tabela_Hash tabela) {
    return NULL;
}