struct dominio {
    char nome[101];
    char ip[16];
    int vezes_consultadas;
} typedef Dominio;

struct no {
    struct no* esquerda;
    struct no* direita;
    Dominio dominio;
} typedef No;

/**
 * 
 */
No *criar_no(Dominio dominio);

/**
 * 
 */
Dominio ler_dominio();

/**
 * 
 */
No *ler_dominios(int n);

/**
 * 
 */
int calcular_altura(No *raiz);

/**
 * 
 */
void inserir_dominio(No **raiz, Dominio dominio);

/**
 * 
 */
Dominio *buscar_dominio(No *raiz, char dominio[101]);

/**
 * 
 */
void destruir_dominios(No *raiz);