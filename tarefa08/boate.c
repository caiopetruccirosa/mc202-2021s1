#include "fila.h"

int main() {
    Fila *fila = ler_fila();

    imprimir_fila(fila);

    destruir_fila(fila);

    return 0;
}