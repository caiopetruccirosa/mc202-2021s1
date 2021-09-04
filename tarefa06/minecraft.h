typedef struct {
    int x, y, z, M;
} Bloco;

/**
 * Cria uma matriz de altitudes representando
 * o relevo de um mundo.
 **/
int **calcularAltitudes(int m, int n, int seed);

/**
 * Cria um novo mundo representado por uma matriz
 * de blocos alocada dinamicamente.
 **/
Bloco ***criarMundo(int m, int n, int **altitudes, int seed);

/**
 * Explora o mapa de um mundo e devolve o tempo
 * necessário para minerar todo ele. Além disso,
 * devolve a quantidade de alguns minérios de
 * interesse.
 **/
double explorarMundo(
    Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco,
    int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos
);

/**
 * Função que imprime as informações sobre quantidade de blocos, minérios e tempo
 * total do mundo na saída padrão.
 **/
void imprimirInformacoes(int qtdBlocos, double tempoTotal, int qtdDiamante, int qtdOuro, int qtdFerro);

/**
 * Função responsável por liberar toda memória alocada dinamicamente na criação 
 * de uma matriz de altitudes em um mundo de minecraft.
 */
void liberarAltitudes(int **altitudes, int m);

/**
 * Função responsável por liberar toda memória alocada dinamicamente na criação 
 * de blocos em um mundo de minecraft.
 */
void liberarMundo(Bloco ***mundo, int m, int n);