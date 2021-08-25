#include <stdio.h>
#include <stdlib.h>

double menor_valor(double a, double b) {
    if (b < a)
        return b;

    return a;
}

void ler_salarios(double salarios[1000][12], int n) {
    for (int i = 0; i < n; i++) {
        char linha[10000], *inicio, *fim;
        fgets(linha, 10000, stdin);

        int j = 0;
        for (inicio = linha; ; inicio = fim) {
            double valor = strtod(inicio, &fim);

            if (inicio == fim) {
                break;
            }
            
            salarios[i][j++] = valor;
        }
    }
}

void ler_abatimentos(double abatimentos[1000], int n) {
    for (int i = 0; i < n; i++) {
        double valor;
        scanf("%lf", &valor);

        abatimentos[i] = valor;
    }
}

void imprimir_tabela(double retido_mes[1000][12], double retido_ano[1000], double anual[1000], int n) {
    printf("Jan\tFev\tMar\tAbr\tMai\tJun\tJul\tAgo\tSet\tOut\tNov\tDez\tRetido\tDevido\tAjuste\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 12; j++) {
            printf("%.2lf\t", retido_mes[i][j]);
        }

        double retido = retido_ano[i];
        double devido = anual[i];
        double ajuste = devido - retido;

        printf("%.2lf\t", retido);
        printf("%.2lf\t", devido);
        printf("%.2lf\t", ajuste);

        printf("\n");
    }

    return;
}

void computar_imposto_retido(double impostos[1000][12], double salarios[1000][12], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 12; j++) {
            double salario = salarios[i][j];
            double retido = 0;

            double aux;

            if (salario > 1499.15) {
                aux = menor_valor(salario, 2246.75) - 1499.15;
                retido += 0.075 * aux;
            }
            
            if (salario > 2246.75) {
                aux = menor_valor(salario, 2995.70) - 2246.75;
                retido += 0.15 * aux;
            }
            
            if (salario > 2995.70) {
                aux = menor_valor(salario, 3743.19) - 2995.70;
                retido += 0.225 * aux;
            } 
            
            if (salario > 3743.19) {
                aux = salario - 3743.19;
                retido += 0.275 * aux;
            }

            impostos[i][j] = retido;
        }
    }
}

void computar_imposto_anual(double impostos[1000], double salarios[1000], double abatimentos[1000], int n) {
    for (int i = 0; i < n; i++) {
        double renda_tributavel = salarios[i] - abatimentos[i];
        double anual = 0;
        double aux;

        if (renda_tributavel > 18000) {
            aux = menor_valor(renda_tributavel, 26400) - 18000;
            anual += 0.075 * aux;
        }
        
        if (renda_tributavel > 26400) {
            aux = menor_valor(renda_tributavel, 36000) - 26400;
            anual += 0.15 * aux;
        }
        
        if (renda_tributavel > 36000) {
            aux = menor_valor(renda_tributavel, 44400) - 36000;
            anual += 0.225 * aux;
        } 
        
        if (renda_tributavel > 44400) {
            aux = renda_tributavel - 44400;
            anual += 0.275 * aux;
        }

        impostos[i] = anual;
    }
}

void somar_entradas(double somas[1000], double valores_a_somar[1000][12], int n) {
    for (int i = 0; i < n; i++) {
        double soma = 0;
        for (int j = 0; j < 12; j++) {
            soma += valores_a_somar[i][j];
        }

        somas[i] = soma;
    }
}

int main() {
    // Le a quantidade de funcionarios
    int n;
    scanf("%d\n", &n);

    // Le os salarios ganhos por mes e os abatimentos para cada funcionarios da entrada padrao
    double salarios_mes[1000][12];
    double abatimentos[1000];
    ler_salarios(salarios_mes, n);
    ler_abatimentos(abatimentos, n);

    // Computa o imposto retido no ano
    double retido_mes[1000][12];
    computar_imposto_retido(retido_mes, salarios_mes, n);

    // Computa os totais de salarios ganhos no ano e impostos retidos no ano
    double salarios_ano[1000];
    double retido_ano[1000];
    somar_entradas(salarios_ano, salarios_mes, n);
    somar_entradas(retido_ano, retido_mes, n);

    // Computa o imposto anual para cada funcionario
    double anual[1000];
    computar_imposto_anual(anual, salarios_ano, abatimentos, n);

    // Imprime a tabela final
    imprimir_tabela(retido_mes, retido_ano, anual, n);

    return 0;
}