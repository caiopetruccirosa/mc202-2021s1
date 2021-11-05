#include <stdio.h>
#include <stdlib.h>
#include "stopwords.h"
#include "comum.h"

/**
 * 
 */
char **ler_stopwords(int s) {
    char **stopwords = malloc(s * sizeof(char*));
    
    for (int i = 0; i < s; i++) {
        stopwords[i] = malloc(TAMANHO_PALAVRA * sizeof(char));
        scanf("%s", stopwords[i]);
    }

    quick_sort(stopwords, 0, s-1);

    return stopwords;
}

/**
 * 
 */
void destruir_stopwords(char **stopwords, int s) {
    for (int i = 0; i < s; i++) {
        free(stopwords[i]);
    }

    free(stopwords);
}

/**
 * 
 */
int eh_stopword(char *palavra, char **stopwords, int s) {
    int idx = busca_binaria(stopwords, 0, s-1, palavra);

    if (idx < 0) {
        return 0;
    } else {
        return 1;
    }
}
