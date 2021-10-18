#include <stdio.h>
#include <stdlib.h>

struct oferta {
    char loja[10];
    int codigo;
    double valor;
} typedef Oferta;

struct no_oferta {
    struct no_oferta *esquerda;
    struct no_oferta *direita;
    struct oferta oferta;
} typedef No_Oferta;

No_Oferta *criar_no_oferta(Oferta oferta) {
    No_Oferta *no = malloc(sizeof(No_Oferta));
    
    no->esquerda = no->direita = NULL;
    no->oferta = oferta;

    return no;
}

void destruir_arvore_ofertas(No_Oferta *raiz) {
    if (raiz == NULL) {
        return;
    }

    destruir_arvore_ofertas(raiz->esquerda);
    destruir_arvore_ofertas(raiz->direita);
    free(raiz);

    return;
}

Oferta ler_oferta() {
    Oferta oferta = {};
    scanf("%s %d %lf", oferta.loja, &oferta.codigo, &oferta.valor);

    return oferta;
}

void inserir_oferta(No_Oferta **raiz, Oferta oferta) {
    if (raiz == NULL) {
        return;
    }

    if (*raiz == NULL) {
        *raiz = criar_no_oferta(oferta);
    } else if (oferta.codigo < (*raiz)->oferta.codigo) {
        inserir_oferta(&(*raiz)->esquerda, oferta);
    } else if (oferta.codigo > (*raiz)->oferta.codigo) {
        inserir_oferta(&(*raiz)->direita, oferta);
    }

    return;
}

Oferta *achar_oferta(No_Oferta *ofertas, int codigo_item) {
    if (ofertas == NULL) {
        return NULL;
    }

    if (ofertas->oferta.codigo == codigo_item) {
        return &ofertas->oferta;
    } else if (codigo_item < ofertas->oferta.codigo) {
        return achar_oferta(ofertas->esquerda, codigo_item);
    } else {
        return achar_oferta(ofertas->direita, codigo_item);
    }
}

void imprimir_ofertas(No_Oferta *ofertas, int codigo_item) {
    printf("OFERTAS para %d:\n", codigo_item);

    Oferta *oferta = achar_oferta(ofertas, codigo_item);

    if (oferta != NULL) {
        printf("%s %d %.2lf\n", oferta->loja, oferta->codigo, oferta->valor);
    } else {
        printf("nenhuma boa oferta foi encontrada\n");
    }

    printf("\n");

    return;
}

int main() {
    int n;
    scanf("%d", &n);

    No_Oferta *ofertas = NULL;
    for (int i = 0; i < n; i++) {
        Oferta oferta = ler_oferta();

        inserir_oferta(&ofertas, oferta);
    }

    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int codigo_item;
        scanf("%d", &codigo_item);

        imprimir_ofertas(ofertas, codigo_item);
    }

    destruir_arvore_ofertas(ofertas);
    
    return 0;
}