#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include <string.h>

#define TAMANHO_NOME_CELA 25
#define TAMANHO_NOME_JOGADOR 25

#define TAMANHO_PERCURSO 2

/**
 * Estrutura que armazena todos os dados de atributos.
 */
struct atributos {
    int forca;
    int destreza;
    int constituicao;
    int inteligencia;
    int sabedoria;
    int carisma;
} typedef Atributos;

/**
 * Estrutura que representa uma cela, contendo o seu nome e um campo de 
 * atributos que representa os atributos mínimos necessários para entrar
 * na cela.
 */
struct cela {
    char nome[TAMANHO_NOME_CELA];
    Atributos atributos_minimos;
} typedef Cela;

/**
 * Estrutura que representa um jogador, armazenando o nome do personagem e
 * o índice da cela em que o personagem irá nascer na primeira rodada.
 */
struct jogador {
    char nome[TAMANHO_NOME_JOGADOR];
    int indice_cela;
} typedef Jogador;

/**
 * Estrutura que representa um grafo de celas, armazenando o número de celas no
 * grafo, um vetor contendo os dados de todas as celas, e uma matriz de adjacências
 * entre as celas no grafo.
 */
struct grafo_cela {
    int numero_vertices;
    Cela *vertices;
    int **arestas;
} typedef Grafo_Cela;

/**
 * Função que retorna o maior valor entre dois números inteiros passados como parâmetro.
 */
int maior(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

/**
 * Função que calcula a diferença entre atributos, sendo que essa diferença se trata
 * de quantos pontos deveriam ser gastos para aprimorar uma habilidade nos atributos
 * "origem" e chegar ao mesmo requisitos cumpridos pelo "destino".
 */
int diferenca_atributos(Atributos origem, Atributos destino) {
    int diferenca = 0;
    diferenca += maior(destino.forca - origem.forca, 0);
    diferenca += maior(destino.destreza - origem.destreza, 0);
    diferenca += maior(destino.constituicao - origem.constituicao, 0);
    diferenca += maior(destino.inteligencia - origem.inteligencia, 0);
    diferenca += maior(destino.sabedoria - origem.sabedoria, 0);
    diferenca += maior(destino.carisma - origem.carisma, 0);
    
    return diferenca;
}

/**
 * Função que lê um grafo de celas.
 * 
 * Essa função aloca memória dinamicamente para a criação do grafo, portanto é
 * responsabilidade do usuário liberá-la ao sistema operacional.
 */
Grafo_Cela *ler_grafo_celas(int n) {
    Grafo_Cela *grafo = malloc(sizeof(Grafo_Cela));

    grafo->numero_vertices = n;
    
    grafo->vertices = malloc(n * sizeof(Cela));
    grafo->arestas = malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        Cela cela;
        scanf("%s %d %d %d %d %d %d",
            cela.nome, 
            &cela.atributos_minimos.forca, 
            &cela.atributos_minimos.destreza, 
            &cela.atributos_minimos.constituicao, 
            &cela.atributos_minimos.inteligencia, 
            &cela.atributos_minimos.sabedoria, 
            &cela.atributos_minimos.carisma);

        grafo->vertices[i] = cela;
        grafo->arestas[i] = malloc(n * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && diferenca_atributos(grafo->vertices[i].atributos_minimos, grafo->vertices[j].atributos_minimos) <= 1) {
                grafo->arestas[i][j] = 1;
            } else {
                grafo->arestas[i][j] = 0;
            }
        }
    }

    return grafo;
}

/**
 * Função que libera toda a memória alocada na construção de um grafo de celas 
 * alocado dinamicamente.
 */
void destruir_grafo(Grafo_Cela *grafo) {
    for (int i = 0; i < grafo->numero_vertices; i++) {
        free(grafo->arestas[i]);
    }

    free(grafo->arestas);
    free(grafo->vertices);
    free(grafo);
}

/**
 * Função que lê as entradas contendo os dados dos jogadores e retorna um vetor
 * de Jogador alocado dinamicamente, logo, é responsabilidade do usuário liberar
 * a memória associada a ele.
 */
Jogador *ler_jogadores(int n, Grafo_Cela *celas) {
    Jogador *jogadores = malloc(n * sizeof(Jogador));

    for (int i = 0; i < n; i++) {
        Atributos atributos;

        scanf("%s %d %d %d %d %d %d", 
            jogadores[i].nome, 
            &atributos.forca, 
            &atributos.destreza, 
            &atributos.constituicao, 
            &atributos.inteligencia, 
            &atributos.sabedoria, 
            &atributos.carisma);
        
        for (int j = 0; j < celas->numero_vertices; j++) {
            if (diferenca_atributos(atributos, celas->vertices[j].atributos_minimos) == 0) {
                jogadores[i].indice_cela = j;
                break;
            }
        }
    }

    return jogadores;
}

/**
 * Função que retorna um valor booleano indicando se existe um percurso entre duas celas 
 * no grafo de celas de tamanho menor ou igual ao tamanho máximo passado. Para isso, é 
 * utilizado o algoritmo de busca BFS.
 */
int existe_percurso(Grafo_Cela *grafo, int origem, int destino, int tamanho_maximo_percurso) {
    int existe_percurso = 0;
    
    Fila a_visitar = criar_fila();

    int *visitados = malloc(grafo->numero_vertices * sizeof(int));
    int *anterior = malloc(grafo->numero_vertices * sizeof(int));
    for (int i = 0; i < grafo->numero_vertices; i++) {
        visitados[i] = anterior[i] = 0;
    }

    enfileirar(&a_visitar, origem);
    visitados[origem] = 1;
    anterior[origem] = -1;

    while (a_visitar.qtd > 0 && !existe_percurso) {
        int vertice_atual = desenfileirar(&a_visitar);

        int tamanho_percurso = 0;
        int vertice_anterior = anterior[vertice_atual];
        while (vertice_anterior >= 0 && tamanho_percurso <= tamanho_maximo_percurso) {
            tamanho_percurso++;
            vertice_anterior = anterior[vertice_anterior];
        }

        if (vertice_atual == destino && tamanho_percurso <= tamanho_maximo_percurso) {
            existe_percurso = 1;
        } else if (tamanho_percurso < tamanho_maximo_percurso) {
            for (int vizinho = 0; vizinho < grafo->numero_vertices; vizinho++) {
                if (grafo->arestas[vertice_atual][vizinho] && !visitados[vizinho]) {
                    enfileirar(&a_visitar, vizinho);
                    visitados[vizinho] = 1;
                    anterior[vizinho] = vertice_atual;
                }
            }
        }
    }

    destruir_fila(a_visitar);
    free(visitados);
    free(anterior);

    return existe_percurso;
}

/**
 * Função que retorna um valor booleano que indica se a cela passada é um ponto de encontro
 * entre os jogadores, passados em formato de vetor, considerando que devem se encontrar em
 * até X rodadas, ou seja, que o tamanho do percurso máximo dos jogadores até a cela passada
 * é menor ou igual a X, nesse caso TAMANHO_PERCURSO.
 */
int eh_ponto_de_encontro(Grafo_Cela *grafo, Jogador *jogadores, int num_jogadores, int destino_cela, int tamanho_maximo_percurso) {
    for (int i = 0; i < num_jogadores; i++) {
        if (!existe_percurso(grafo, jogadores[i].indice_cela, destino_cela, tamanho_maximo_percurso)) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int numero_celas;
    scanf("%d", &numero_celas);
    Grafo_Cela *celas = ler_grafo_celas(numero_celas);

    int numero_jogadores;
    scanf("%d", &numero_jogadores);
    Jogador* jogadores = ler_jogadores(numero_jogadores, celas);

    int eh_possivel = 0;
    for (int i = 0; i < numero_celas; i++) {
        if (eh_ponto_de_encontro(celas, jogadores, numero_jogadores, i, TAMANHO_PERCURSO)) {
            printf("%s\n", celas->vertices[i].nome);
            eh_possivel = 1;
        }
    }

    // caso não tenha imprimido nenhum nome, "eh_possivel" terá o valor 0.
    if (!eh_possivel)
        printf("Impossivel terminar em duas rodadas.\n");

    destruir_grafo(celas);
    free(jogadores);

    return 0;
}