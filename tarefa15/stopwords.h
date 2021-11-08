#ifndef STOPWORDS
#define STOPWORDS

#ifndef TAMANHO_PALAVRA
#define TAMANHO_PALAVRA 51
#endif

/**
 * 
 */
int particionamento_stopwords(char **vetor, int inicio, int fim);

/**
 * 
 */
void quick_sort_stopwords(char **vetor, int inicio, int fim);

/**
 * 
 */
int busca_binaria_stopwords(char **vetor, int inicio, int fim, char *valor);

/**
 * Função que filtra todos os caracteres alphanuméricos de uma string
 * passada como parâmetro e transforma todos os caracteres para lowercase.
 */
void tratar_palavra(char *palavra);

/**
 * 
 */
char **ler_stopwords(int s);

/**
 * 
 */
void destruir_stopwords(char **stopwords, int s);

/**
 * 
 */
int eh_stopword(char *palavra, char **stopwords, int s);

#endif