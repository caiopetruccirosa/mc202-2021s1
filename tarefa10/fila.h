struct navio {
    char nome[21];
    char objetivo[11];
    char tipo_mercadoria[21];
    int carga;
} typedef Navio;

struct no {
    struct navio *navio;
    struct no *proximo;
} typedef No;

struct fila {
    No* inicio;
    No* fim;
    int qtd;
} typedef Fila;

/**
 * Função responsável por alocar e inicializar uma struct do tipo No, a partir de
 * uma struct do tipo Navio passada como parâmetro. 
 * 
 * Portanto, a estrutura foi alocada dinamicamente e é responsabilidade do usuário 
 * liberar a memória envolvida.
 */
No *criar_no(Navio navio);

/**
 * Função responsável por liberar toda a memória que envolve a struct do tipo No, 
 * liberando a própria estrutura assim como a estrutura do dado associado a esse nó.
 */
void destruir_no(No *no);

/**
 * Função responsável por alocar e inicializar uma struct do tipo Fila e retornar
 * um ponteiro para a estrutura. 
 * 
 * Portanto, a estrutura foi alocada dinamicamente e é responsabilidade do usuário 
 * liberar a memória envolvida.
 */
Fila criar_fila_navios();

/**
 * Função responsável por liberar toda a memória que envolve a struct do tipo Fila, 
 * liberando a própria estrutura assim como todos os nós e os dados armazenados nela.
 */
void destruir_fila_navios(Fila fila);

/**
 * Função que lê os dados de uma fila de navios da entrada padrão (stdin).
 */
Fila ler_fila_navios(int numero_navios);

/**
 * Função responsável por enfileirar um navio em uma fila.
 * 
 * São passados como parâmetros para a função um ponteiro para a fila que deve ser
 * incrementada e o navio que deve ser enfileirado.
 */
void enfileirar(Fila *fila, Navio navio);

/**
 * Função responsável por desenfileirar o primeiro navio de uma fila.
 * 
 * A função libera a memória do nó desenfileirado e retorna o navio que estava
 * sendo armazenado.
 */
Navio desenfileirar(Fila *fila);

/**
 * Função que retorna um valor booleano indicando se a fila está vazia.
 */
int eh_fila_vazia(Fila fila);
