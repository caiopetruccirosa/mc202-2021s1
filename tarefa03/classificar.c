#include <stdio.h>
#include <string.h>

void ler_nomes(char nomes[100][30], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%s", nomes[i]);
    }
}

void imprimir_nomes(char nomes[100][30], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", nomes[i]);
    }
}

int posicao_separador(char nome[30]) {
    int i = 0;

    while (1 == 1) {
        if (nome[i] == '\0') {
            return -1;
        } else if (nome[i] == '_') {
            return i;
        }

        i++;
    }

    return -1;
}

int comparar_parentes(char nome1[30], char nome2[30]) {
    int i = posicao_separador(nome1);
    int j = posicao_separador(nome2);

    int ret = strcmp(&nome1[i], &nome2[j]);
    if (ret == 0) {
        ret = strcmp(nome1, nome2);
    }

    return ret;
}

int sao_parentes(char nome1[30], char nome2[30]) {
    int i = posicao_separador(nome1);
    int j = posicao_separador(nome2);

    if (strcmp(&nome1[i], &nome2[j]) != 0) {
        return 0;
    }

    return 1;
}

int sao_homonimos(char nome1[30], char nome2[30]) {
    char primeiro_nome1[30];
    strcpy(primeiro_nome1, nome1);
    primeiro_nome1[posicao_separador(primeiro_nome1)] = '\0';

    char primeiro_nome2[30];
    strcpy(primeiro_nome2, nome2);
    primeiro_nome2[posicao_separador(primeiro_nome2)] = '\0';

    if (strcmp(primeiro_nome1, primeiro_nome2) != 0) {
        return 0;
    }

    return 1;
}

void ordenar(char v[100][30], int n) {
    for (int i = 0; i < n; i++) {
        int menor = i;

        for (int j = i; j < n; j++) {
            if (strcmp(v[j], v[menor]) < 0) {
                menor = j;
            }
        }

        if (menor != i) {
            char aux[30];
            strcpy(aux, v[i]);
            strcpy(v[i], v[menor]);
            strcpy(v[menor], aux);
        }
    }

    return;
}

void ordenar_parentes(char v[100][30], int n) {
    for (int i = 0; i < n; i++) {
        int menor = i;

        for (int j = i; j < n; j++) {
            if (comparar_parentes(v[j], v[menor]) < 0) {
                menor = j;
            }
        }

        if (menor != i) {
            char aux[30];
            strcpy(aux, v[i]);
            strcpy(v[i], v[menor]);
            strcpy(v[menor], aux);
        }
    }

    return;
}

void achar_homonimos(char homonimos[100][30], int *n, char nomes[100][30], int m) {
    *n = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i != j && sao_homonimos(nomes[i], nomes[j]) == 1) {
                strcpy(homonimos[*n], nomes[i]);
                (*n)++;
                break;
            }
        }
    }

    ordenar(homonimos, *n);

    return;
}

void achar_parentes(char parentes[100][30], int *n, char nomes[100][30], int m) {
    *n = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (i != j && sao_parentes(nomes[i], nomes[j]) == 1) {
                strcpy(parentes[*n], nomes[i]);
                (*n)++;
                break;
            }
        }
    }

    ordenar_parentes(parentes, *n);

    return;
}

int main() {
    int n;
    scanf("%d", &n);

    char opcao[10];
    scanf("%s", opcao);

    char nomes[100][30];
    ler_nomes(nomes, n);

    int m;
    char resultado[100][30];
    if (strcmp(opcao, "homonimos") == 0) {
        achar_homonimos(resultado, &m, nomes, n);
    } else if (strcmp(opcao, "parentes") == 0) {
        achar_parentes(resultado, &m, nomes, n);
    }

    imprimir_nomes(resultado, m);

    return 0;
}