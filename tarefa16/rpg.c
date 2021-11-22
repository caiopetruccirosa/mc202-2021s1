#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

#define TAMANHO_NOME_CELA 100
#define TAMANHO_NOME_JOGADOR 100

#define TAMANHO_PERCURSO 2

/**
 * 
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
 * 
 */
struct cela {
    char nome[TAMANHO_NOME_CELA];
    Atributos atributos_minimos;
} typedef Cela;

/**
 * 
 */
struct jogador {
    char nome[TAMANHO_NOME_JOGADOR];
    Atributos atributos;
    int indice_cela;
} typedef Jogador;

/**
 * 
 */
struct grafo {
    int numero_vertices;
    Cela *vertices;
    int **arestas;
} typedef Grafo;

/**
 * 
 */
int maior(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

/**
 * 
 */
int diferenca_atributos(Atributos origem, Atributos destino) {
    int diferenca = maior(destino.forca - origem.forca, 0);
    diferenca += maior(destino.destreza - origem.destreza, 0);
    diferenca += maior(destino.constituicao - origem.constituicao, 0);
    diferenca += maior(destino.inteligencia - origem.inteligencia, 0);
    diferenca += maior(destino.sabedoria - origem.sabedoria, 0);
    diferenca += maior(destino.carisma - origem.carisma, 0);
    
    return diferenca;
}

/**
 * 
 */
Cela *ler_celas(int n) {
    Cela *celas = malloc(n * sizeof(Cela));

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d %d %d %d", 
            celas[i].nome, 
            &celas[i].atributos_minimos.forca, 
            &celas[i].atributos_minimos.destreza, 
            &celas[i].atributos_minimos.constituicao, 
            &celas[i].atributos_minimos.inteligencia, 
            &celas[i].atributos_minimos.sabedoria, 
            &celas[i].atributos_minimos.carisma);
    }

    return celas;
}

/**
 * 
 */
Jogador *ler_jogadores(int n) {
    Jogador *jogadores = malloc(n * sizeof(Jogador));

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d %d %d %d %d", 
            jogadores[i].nome, 
            &jogadores[i].atributos.forca, 
            &jogadores[i].atributos.destreza, 
            &jogadores[i].atributos.constituicao, 
            &jogadores[i].atributos.inteligencia, 
            &jogadores[i].atributos.sabedoria, 
            &jogadores[i].atributos.carisma);
        
        jogadores[i].indice_cela = -1;
    }

    return jogadores;
}

/**
 * 
 */
Grafo criar_grafo(Cela *celas, int numero_celas) {
    Grafo grafo;

    grafo.numero_vertices = numero_celas;
    
    grafo.vertices = malloc(numero_celas * sizeof(Cela));
    grafo.arestas = malloc(numero_celas * sizeof(int*));

    for (int i = 0; i < numero_celas; i++) {
        grafo.vertices[i] = celas[i];
        grafo.arestas[i] = malloc(numero_celas * sizeof(int));

        for (int j = 0; j < numero_celas; j++) {
            if (i != j && diferenca_atributos(celas[i].atributos_minimos, celas[j].atributos_minimos) <= 1) {
                grafo.arestas[i][j] = 1;
            } else {
                grafo.arestas[i][j] = 0;
            }
        }
    }

    return grafo;
}

/**
 * 
 */
void destruir_grafo(Grafo grafo) {
    for (int i = 0; i < grafo.numero_vertices; i++) {
        free(grafo.arestas[i]);
    }

    free(grafo.arestas);
    free(grafo.vertices);
}

/**
 * 
 */
int eh_cela_destino(Grafo grafo, int origem, int destino) {
    Fila a_visitar = criar_fila();

    int *visitados = malloc(grafo.numero_vertices * sizeof(int));
    int *anterior = malloc(grafo.numero_vertices * sizeof(int));
    for (int i = 0; i < grafo.numero_vertices; i++) {
        visitados[i] = anterior[i] = 0;
    }

    enfileirar(&a_visitar, origem);
    visitados[origem] = 1;
    anterior[origem] = -1;

    while (a_visitar.qtd > 0) {
        int vertice_atual = desenfileirar(&a_visitar);

        int tamanho_percurso = 0;
        int vertice_anterior = anterior[vertice_atual];
        while (vertice_anterior >= 0 && tamanho_percurso <= TAMANHO_PERCURSO) {
            tamanho_percurso++;
            vertice_anterior = anterior[vertice_anterior];
        }

        if (vertice_atual == destino && tamanho_percurso <= TAMANHO_PERCURSO) {
            return 1;
        } else if (tamanho_percurso < TAMANHO_PERCURSO) {
            for (int vizinho = 0; vizinho < grafo.numero_vertices; vizinho++) {
                if (grafo.arestas[vertice_atual][vizinho] && !visitados[vizinho]) {
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

    return 0;
}

/**
 * 
 */
void achar_celas(Jogador *jogadores, int num_jogadores, Cela *celas, int num_celas) {
    for (int i = 0; i < num_jogadores; i++) {
        for (int j = 0; j < num_celas; j++) {
            if (diferenca_atributos(jogadores[i].atributos, celas[j].atributos_minimos) == 0) {
                jogadores[i].indice_cela = j;
                break;
            }
        }
    }
}

/**
 * 
 */
int eh_ponto_encontro(Grafo grafo, Jogador *jogadores, int num_jogadores, int destino_cela) {
    for (int i = 0; i < num_jogadores; i++) {
        if (!eh_cela_destino(grafo, jogadores[i].indice_cela, destino_cela)) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int numero_celas;
    scanf("%d", &numero_celas);
    Cela* celas = ler_celas(numero_celas);

    int numero_jogadores;
    scanf("%d", &numero_jogadores);
    Jogador* jogadores = ler_jogadores(numero_jogadores);

    achar_celas(jogadores, numero_jogadores, celas, numero_celas);

    Grafo grafo = criar_grafo(celas, numero_celas);

    int contagem = 0;
    for (int i = 0; i < numero_celas; i++) {
        if (eh_ponto_encontro(grafo, jogadores, numero_jogadores, i)) {
            printf("%s\n", celas[i].nome);
            contagem++;
        }
    }

    if (contagem == 0) {
        printf("Impossivel terminar em duas rodadas.\n");
    }

    destruir_grafo(grafo);

    free(jogadores);
    free(celas);

    return 0;
}