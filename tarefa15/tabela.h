#ifndef TABELA_HASH
#define TABELA_HASH

#define TAMANHO_PALAVRA 51

struct contador {
    char palavra[TAMANHO_PALAVRA]; // chave
    int contagem;                  // valor
} typedef Contador;

struct tabela_hash {
    Contador **vetor;
    int capacidade;
} typedef Tabela_Hash;

/**
 * 
 */
Tabela_Hash criar_tabela(int capacidade);

/**
 * 
 */
void destruir_tabela(Tabela_Hash tabela);

/**
 * 
 */
unsigned long int hash(char palavra[TAMANHO_PALAVRA]);

/**
 * 
 */
int buscar_contagem(Tabela_Hash tabela, char palavra[TAMANHO_PALAVRA]);

/**
 * 
 */
void incrementar_contagem(Tabela_Hash *tabela, char palavra[TAMANHO_PALAVRA]);

/**
 * 
 */
void imprimir_tabela(Tabela_Hash tabela);

#endif