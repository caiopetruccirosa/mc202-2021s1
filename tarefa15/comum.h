#ifndef COMUM
#define COMUM

#define TAMANHO_PALAVRA 51

/**
 * 
 */
int particionamento(char **vetor, int inicio, int fim);

/**
 * 
 */
void quick_sort(char **vetor, int inicio, int fim);

/**
 * 
 */
int busca_binaria(char **vetor, int inicio, int fim, char *valor);

/**
 * 
 */
void filtrar_nao_alphanumericos(char *palavra);

#endif