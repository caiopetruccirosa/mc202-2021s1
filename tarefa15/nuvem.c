#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stopwords.h"
#include "tabela.h"

int main() {
    int n, s; // número de palavras distintas e número de stop words respectivamente
    scanf("%d %d ", &n, &s);

    char **stopwords = ler_stopwords(s);

    Tabela_Hash tabela = criar_tabela(n);

    char palavra[TAMANHO_PALAVRA];
    while(scanf("%s", palavra) != EOF) {
        tratar_palavra(palavra);
        
        if (!eh_stopword(palavra, stopwords, s) && strlen(palavra) > 1) {
            incrementar_contagem(&tabela, palavra);
        }
    }

    imprimir_palavras_mais_frequentes(tabela);

    destruir_stopwords(stopwords, s);
    destruir_tabela(tabela);

    return 0;
}