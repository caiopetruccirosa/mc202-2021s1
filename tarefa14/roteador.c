#include <stdio.h>
#include <stdlib.h>

/**
 * Estrutura que armazena os dados de um pacote recebido
 * pelo roteador
 */
struct pacote {
    int id;
    int prioridade;
    int incremento;
} typedef Pacote;

typedef Pacote* Fila_Pacotes;

/**
 * Função que cria um vetor de m pacotes e initializa o vetor
 * com valores "zero". O espaço do vetor é alocado dinamicamente,
 * portanto, deve ser liberado pelo usuário.
 */
Fila_Pacotes criar_fila_pacotes(int m) {
    Pacote *pacotes = malloc(m * sizeof(Pacote));
    
    for (int i = 0; i < m; i++) {
        Pacote p = { 0, 0, 0 };
        pacotes[i] = p;
    }

    return pacotes;
}

/**
 * Função que insere um pacote na fila de prioridades de
 * pacotes, de tamanho m, caso haja espaço para inserção.
 * Caso contrário, o pacote é ignorado.
 */
void inserir_pacote(Fila_Pacotes pacotes, int m, int id, int prioridade, int incremento, int i) {
    if (i >= m) {
        return;
    }

    Pacote p = { id, prioridade, incremento };
    pacotes[i] = p;

    return;
}

/**
 * 
 */
void incrementar_prioridades(Fila_Pacotes pacotes, int m) {
    return;
}

/**
 * Função que executa um tick, de número c, onde os k pacotes
 * com prioridade na fila de prioridade, de tamanho m, serão 
 * removidos, caso possível.
 */
void tick(Fila_Pacotes pacotes, int m, int k, int c) {
    printf("TICK %d\n", c);
    for (int i = 0; i < m && i < k; i++) {
        Pacote p = pacotes[i];
        printf("%d\t%d\t%d\n", p.id, p.incremento, p.incremento);
    }
    printf("\n");

    return;
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);

    Fila_Pacotes pacotes = criar_fila_pacotes(m);

    int contador_tick = 0, i = 0;
    int id, prioridade, incremento;
    while (scanf("%d %d %d", &id, &prioridade, &incremento) != EOF) {
        if (id == 0 && prioridade == 0 && incremento == 0) {
            tick(pacotes, m, k, ++contador_tick);
            incrementar_prioridades(pacotes, m);
        } else if (i < m) {
            inserir_pacote(pacotes, m, id, prioridade, incremento, i++);
        }
    }

    return 0;
}