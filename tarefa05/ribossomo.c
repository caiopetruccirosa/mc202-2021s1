#include <stdio.h>
#include <stdlib.h>

/**
 * Função que inicializa um vetor 'v' de inteiros de tamanho 'n' e zera
 * todos os elementos.
 */
void inicializar_vetor_zerado(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = 0;
    }
}

/**
 * Função que encontra um elemento em um vetor 'v' de tamanho 'n' e retorna 
 * a posição do elemento. Caso o elemento não seja encontrado, retorna -1.
 */
int encontrar(char elem, char v[], int n) {
    for (int i = 0; i < n; i++) {
        if (elem == v[i]) {
            return i;
        }
    }

    return -1;
}

/**
 * Função que transcreve um segmento de DNA e preenche um vetor 'segmento_transcrito',
 * baseado nos 'padrao_dna' e 'padrao_rna', e preenche o vetor 'id_transcricao'.
 */
void transcrever_dna(int *id_transcricao, char *segmento, char *segmento_transcrito, int n, char padrao_dna[14], char padrao_rna[14]) {
    int contador_transcricao[13];
    inicializar_vetor_zerado(contador_transcricao, 13);

    for (int i = 0; i < n; i++) {
        int idx = encontrar(segmento[i], padrao_dna, 13);

        id_transcricao[i] = contador_transcricao[idx];
        segmento_transcrito[i] = padrao_rna[idx];
        contador_transcricao[idx]++;
    }

    return;
}

/**
 * Função que imprime um diagrama, baseado em vetores dos "ids de transcrição", do 
 * segmento original e do segmento transcrito, todos de tamanho 'n'.
 */
void imprimir_diagrama(int *id_transcricao, char *segmento, char *segmento_transcrito, int n) {
    printf("ID:\t");
    for (int i = 0; i < n; i++) {
        printf("%d", id_transcricao[i]);

        if (i < n - 1) {
            printf("\t");
        }
    }

    printf("\nDNA:\t");
    for (int i = 0; i < n; i++) {
        printf("%c", segmento[i]);

        if (i < n - 1) {
            printf("\t");
        }
    }

    printf("\n\t");
    for (int i = 0; i < n; i++) {
        printf("|");

        if (i < n - 1) {
            printf("\t");
        }
    }

    printf("\nRNA:\t");
    for (int i = 0; i < n; i++) {
        printf("%c", segmento_transcrito[i]);

        if (i < n - 1) {
            printf("\t");
        }
    }
    printf("\n");

    return;
}

int main() {
    char padrao_dna[14];
    scanf("%s", padrao_dna);

    char padrao_rna[14];
    scanf("%s", padrao_rna);

    int n;
    scanf("%d", &n);

    char *segmento = malloc(n * sizeof(char) + 1);
    scanf("%s", segmento);

    char *segmento_transcrito = malloc(n * sizeof(char) + 1);
    scanf("%s", segmento_transcrito);

    int contador_transcricao[13];
    inicializar_vetor_zerado(contador_transcricao, 13);
    
    int *id_transcricao = malloc(n * sizeof(int));
    inicializar_vetor_zerado(id_transcricao, n);

    transcrever_dna(id_transcricao, segmento, segmento_transcrito, n, padrao_dna, padrao_rna);

    imprimir_diagrama(id_transcricao, segmento, segmento_transcrito, n);

    free(segmento);
    free(segmento_transcrito);
    free(id_transcricao);

    return 0;
}