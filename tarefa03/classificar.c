#include <stdio.h>
#include <string.h>

/*
Função que lê uma quantidade 'n' de nomes de até 29 caracteres da entrada padrão.
Conforme a leitura, a função popula um vetor de strings 'nomes' com os nomes lidos.
*/
void ler_nomes(char nomes[100][30], int n) {
    for (int i = 0; i < n; i++) {
        scanf("%s", nomes[i]);
    }
}

/*
Função que imprime uma quantidade 'n' de nomes de até 29 caracteres na saída padrão.
Os nomes devem ser passados em um vetor de strings 'nomes' de tamanho 'n'.
*/
void imprimir_nomes(char nomes[100][30], int n) {
    for (int i = 0; i < n; i++) {
        printf("%s\n", nomes[i]);
    }
}

/*
Função que, dado um nome de até 29 caracteres, encontra e retorna a posição do separador
'_' dentro da string.
*/
int posicao_separador(char nome[30]) {
    for (int i = 0; i < 30 && nome[i] != '\0'; i++) {
        if (nome[i] == '_') {
            return i;
        }
    }

    return -1;
}

/*
Função que compara dois nomes, lexicograficamente, priorizando na comparação a lexicografia
dos sobrenomes e então, se forem iguais, a lexicografia do nome completo.
A função retorna:
- -1 se nome1 < nome2;
- 0 se nome1 == nome2;
- 1 se nome1 > nome2.
*/
int comparar_sobrenome(char nome1[30], char nome2[30]) {
    int separador_nome1 = posicao_separador(nome1);
    int separador_nome2 = posicao_separador(nome2);

    int comparacao = strcmp(&nome1[separador_nome1], &nome2[separador_nome2]);
    if (comparacao == 0) {
        comparacao = strcmp(nome1, nome2);
    }

    return comparacao;
}

/*
Função que, dados dois nomes de até 29 caracteres, retorna um valor booleano (0 para 
falso e 1 para verdadeiro) que indica se os nomes representam individuos parentes, ou 
seja, com sobrenomes iguais.
*/
int sao_parentes(char nome1[30], char nome2[30]) {
    int i = posicao_separador(nome1);
    int j = posicao_separador(nome2);

    if (strcmp(&nome1[i], &nome2[j]) != 0) {
        return 0;
    }

    return 1;
}

/*
Função que, dados dois nomes de até 29 caracteres, retorna um valor booleano (0 para 
falso e 1 para verdadeiro) que indica se os nomes são homonimos, a partir da comparação
apenas dos primeiros nomes de cada nome.
*/
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

/*
Função que faz o particionamento de um vetor de nomes em duas partições baseadas em 
um  pivô escolhido, onde uma partição contem nomes "menores" do que o pivô e a outra 
contem valor "maiores", baseado em uma 'opcao' de ordenação que resulta em regras
diferentes de ordem.
*/
int particionamento(char v[100][30], int inicio, int fim, char opcao[10]) {    
    int posicao_pivo = fim;

    int i = inicio;
    for (int j = inicio; j < fim; j ++) {
        if ((strcmp(opcao, "parentes") == 0 && comparar_sobrenome(v[j], v[posicao_pivo]) < 0) || 
            (strcmp(opcao, "homonimos") == 0 && strcmp(v[j], v[posicao_pivo]) < 0)) {
            
            char aux[30];
            strcpy(aux, v[i]);
            strcpy(v[i], v[j]);
            strcpy(v[j], aux);

            i++;
        }
    }

    // Coloca o pivô no lugar dele
    if (i != posicao_pivo) {
        char aux[30];
        strcpy(aux, v[i]);
        strcpy(v[i], v[posicao_pivo]);
        strcpy(v[posicao_pivo], aux);

        posicao_pivo = i;
    }

    return posicao_pivo;
}

/*
Função que ordena um vetor de strings, de até 29 caracteres, utilizando o algoritmo
recursivo quick_sort, baseado em uma 'opcao' de ordenação, que pode ser "homonimos" 
ou "parentes". 
*/
void quick_sort(char v[100][30], int inicio, int fim, char opcao[10]) {
    if (inicio < fim) {
        int posicao_pivo = particionamento(v, inicio, fim, opcao);

        quick_sort(v, inicio, posicao_pivo-1, opcao);
        quick_sort(v, posicao_pivo+1, fim, opcao);
    }

    return;
}


/*
Função que ordena um vetor de nomes (de até 29 caracteres) de tamanho 'n'.
Para a ordenação, é necessário passar uma 'opcao' de ordenação, que pode ser "homonimos" 
ou "parentes" onde cada uma resulta em regras de ordenação diferentes.
*/
void ordenar_nomes(char nomes[100][30], int n, char opcao[10]) {
    quick_sort(nomes, 0, n-1, opcao);

    return;
}

/*
Função que filtra os nomes em um vetor 'nomes' baseado em uma 'opcao', que pode conter os
valores "homonimos" ou "parentes", e armazena os valores filtrados em um vetor 'filtrados'
que terá tamanho 'm'.
*/
void filtrar_nomes(char nomes[100][30], int n, char filtrados[100][30], int *m, char opcao[10]) {
    *m = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                if ((strcmp(opcao, "homonimos") == 0 && sao_homonimos(nomes[i], nomes[j])) || 
                    (strcmp(opcao, "parentes") == 0 && sao_parentes(nomes[i], nomes[j]))) {
                    
                    strcpy(filtrados[*m], nomes[i]);
                    (*m)++;

                    break;
                }
            }
        }
    }

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
    char classificados[100][30];
    filtrar_nomes(nomes, n, classificados, &m, opcao);
    ordenar_nomes(classificados, m, opcao);

    imprimir_nomes(classificados, m);

    return 0;
}