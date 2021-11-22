/**
 * 
 */
struct no_fila {
    int valor;
    struct no_fila *proximo;
} typedef No_Fila;

/**
 * 
 */
struct fila {
    int qtd;
    No_Fila *inicio;
    No_Fila *fim;
} typedef Fila;

/**
 * 
 */
Fila criar_fila();

/**
 * 
 */
void destruir_fila(Fila fila);

/**
 * 
 */
void enfileirar(Fila *fila, int valor);

/**
 * 
 */
int desenfileirar(Fila *fila);