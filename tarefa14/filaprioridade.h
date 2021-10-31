#ifndef FILA_PRIORIDADE
#define FILA_PRIORIDADE

/**
 * Estrutura que armazena os dados de um pacote recebido
 * pelo roteador
 */
struct pacote {
    int id;
    int prioridade;
    int incremento;
} typedef Pacote;

/**
 * Estrutura que armazena os dados da fila de prioridade que contem
 * o max-heap
 */
struct fila_prioridade {
    Pacote *v;
    int i, tamanho;
} typedef Fila_Prioridade;

/**
 * Função que cria uma fila de prioridade de m pacotes e initializa o 
 * vetor com valores "zero". O espaço do vetor é alocado dinamicamente,
 * portanto, deve ser liberado pelo usuário.
 */
Fila_Prioridade *criar_fila_prioridade(int m);

/**
 * Função que retorna um valor booleano indicando se a fila 
 * de prioridade está vazia.
 */
int esta_vazia(Fila_Prioridade *fila);

/**
 * Função que retorna um valor booleano indicando se a fila 
 * de prioridade está cheia.
 */
int esta_cheia(Fila_Prioridade *fila);

/**
 * Função que troca dois pacotes de posição baseado na posição da memória,
 * ou seja, nos ponteiros que indicam suas posições iniciais.
 */
void trocar(Pacote *a, Pacote *b);

/**
 * Função que sobe um pacote no heap da fila de prioridade recursivamente, 
 * trocando o pacote pelo seu pai enquanto for possível.
 */
void subir_no_heap(Fila_Prioridade *fila, int k);

/**
 * Função que desce um pacote no heap da fila de prioridade recursivamente, 
 * trocando o pacote pelo seu filho de maior prioridade, enquanto for possível.
 */
void descer_no_heap(Fila_Prioridade *fila, int k);

/**
 * Função que insere um pacote na fila de prioridades de pacotes, caso haja espaço 
 * para inserção. Caso contrário, o pacote é ignorado.
 */
void inserir_pacote(Fila_Prioridade *fila, Pacote p);

/**
 * Função que extrai o pacote com prioridade máxima da fila de prioridade e
 * mantêm as propriedades da fila de prioridade.
 */
Pacote extrair_maximo(Fila_Prioridade *fila);

/**
 * Função que incrementa a prioridade de um pacote na posição k da fila de prioridade
 * de acordo com os seus respectivos incrementos e mantêm as propriedades da fila 
 * de prioridade.
 */
void incrementa_prioridade(Fila_Prioridade *fila, int k);

/**
 * Função que incrementa a prioridade de todos os pacotes da fila de prioridade
 * de acordo com os seus respectivos incrementos e mantêm as propriedades da fila 
 * de prioridade.
 */
void incrementar_prioridades(Fila_Prioridade *fila);

/**
 * Função que libera toda a memória alocada dinamicamente para a criação de uma
 * fila de prioridade.
 */
void destruir_fila_prioridade(Fila_Prioridade *fila);

#endif