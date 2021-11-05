#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "comum.h"
#include "stopwords.h"
#include "tabela.h"

int main() {
    int n, s; // número de palavras distintas e número de stop words respectivamente
    scanf("%d %d ", &n, &s);

    char **stopwords = ler_stopwords(s);
    Tabela_Hash tabela = criar_tabela(n);

    char palavra[TAMANHO_PALAVRA];
    while(scanf("%s", palavra) != EOF) {
        filtrar_nao_alphanumericos(palavra);

        if (!eh_stopword(palavra, stopwords, s)) {
            incrementar_contagem(&tabela, palavra);
        }
    }

    char **mais_frequentes = palavras_mais_frequentes(tabela);

    destruir_stopwords(stopwords, s);
    destruir_tabela(tabela);

    return 0;
}