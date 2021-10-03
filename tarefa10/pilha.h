struct conteiner {
    char tipo_mercadoria[21];
} typedef Conteiner;

struct pilha {
    Conteiner *v;
    int topo;
    int capacidade;
} typedef Pilha;

/**
 * 
 */
Pilha criar_pilha(int capacidade);

/**
 * 
 */
void empilhar(Pilha *pilha, Conteiner conteiner);

/**
 * 
 */
Conteiner desempilhar(Pilha *pilha);