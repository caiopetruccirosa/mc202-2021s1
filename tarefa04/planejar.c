#include <stdio.h>
#include <string.h>
#include "planejar.h"

/*
    Função que lê uma data da entrada padrão (stdin), no formato DD/MM/AAAA,
    e retorna uma struct do tipo "Data".
*/
Data ler_data() {
    int dia, mes, ano;

    scanf("%d/%d/%d", &dia, &mes, &ano);

    Data data = { 
        dia: dia,
        mes: mes,
        ano: ano
    };

    return data;
}

/*
    Função que compara duas datas do tipo "Data" e retorna um inteiro:
    - -1 se data1 < data2;
    - 0 se data1 == data2;
    - 1 se data1 > data2;
*/
int compara_data(Data data1, Data data2) {
    if (data1.ano < data2.ano) {
        return -1;
    } else if (data1.ano > data2.ano) {
        return 1;
    }

    if (data1.mes < data2.mes) {
        return -1;
    } else if (data1.mes > data2.mes) {
        return 1;
    }

    if (data1.dia < data2.dia) {
        return -1;
    } else if (data1.dia > data2.dia) {
        return 1;
    }

    return 0;
}

/*
    Função que calcula a diferença entre as datas data1 e data2 e retorna o número de
    dias de diferença entre elas. A operação realizada é análoga à |data1 - data2|.
*/
int diferenca_data(Data data1, Data data2) {
    int dias_por_mes[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    Data data_maior = data1;
    Data data_menor = data2;

    if (compara_data(data1, data2) < 0) {
        data_maior = data2;
        data_menor = data1;
    }

    int ano_diff = data_maior.ano - data_menor.ano;
    int mes_diff = (data_maior.mes - data_menor.mes) + 12 * ano_diff;
    int dias_diff = 0;

    for (int i = 0; i < mes_diff; i++) {
        int indice_mes = (data_menor.mes - 1 + i) % 12;

        dias_diff += dias_por_mes[indice_mes];
    }

    dias_diff += data_maior.dia - (data_menor.dia - 1);
 
    return dias_diff;
}

/*
    Função que registra um voo novo em uma lista de voos, adicionando uma estrutura nova
    de voo ao final do vetor 'voos' e incrementa o seu tamanho.
*/
void registrar(Voo voos[], int *qtd_voos, int numero_voo, char origem_novo[], char destino_novo[], Data data, float valor) {
    Voo novo_voo = {
        numero: numero_voo,
        origem: origem_novo,
        destino: destino_novo,
        data: data,
        valor: valor
    };

    voos[*qtd_voos] = novo_voo;

    (*qtd_voos)++;
    
    return;
}

/*
    Função que cancela um voo, removendo um voo de um vetor de 'voos'.
*/
void cancelar(Voo voos[], int *qtd_voos, int numero_voo) {
    for (int i = 0; i < *qtd_voos; i++) {
        if (voos[i].numero == numero_voo) {
            voos[i] = voos[--(*qtd_voos)];
            break;
        }
    }

    return;
}

/*
    Função que altera o valor (preço) de um voo dentro do vetor de 'voos', cujo o
    número do voo seja o número passado ('numero_voo').
*/
void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor) {
    for (int i = 0; i < qtd_voos; i++) {
        if (voos[i].numero == numero_voo) {
            voos[i].valor = novo_valor;
            break;
        }
    }
    
    return;
}

/*
    Função que planeja a viagem de Dumont e imprime os números de voo dos voos de
    ida e volta, respectivamente, de forma que sejam os voos mais baratos do vetor
    'voos'.
*/
void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[]) {
    int numero_voo_ida, numero_voo_volta;
    float menor_soma_valores = -1.0;

    for (int i = 0; i < qtd_voos; i++) {
        Voo voo_ida = voos[i];

        if (strcmp(voo_ida.origem, codigo_origem) == 0 &&
            compara_data(voo_ida.data, data_inicio) >= 0 &&
            compara_data(voo_ida.data, data_fim) < 0) {

            for (int j = 0; j < qtd_voos; j++) {
                Voo voo_volta = voos[j];

                if (strcmp(voo_volta.destino, codigo_origem) == 0 && 
                    diferenca_data(voo_ida.data, voo_volta.data) >= 4 &&
                    compara_data(voo_ida.data, voo_volta.data) < 0 &&
                    compara_data(voo_volta.data, data_fim) <= 0 &&
                    compara_data(voo_volta.data, data_inicio) > 0) {
                        
                    float somaAux = voo_ida.valor + voo_volta.valor;

                    if (menor_soma_valores < 0 || somaAux < menor_soma_valores) {
                        menor_soma_valores = somaAux;
                        numero_voo_ida = voo_ida.numero;
                        numero_voo_volta = voo_volta.numero;
                    }
                }
            }
        }
    }

    // imprime o número do voo de ida da viagem de menor custo
    printf("%d\n", numero_voo_ida);

    // imprime o número do voo de volta da viagem de menor custo
    printf("%d\n", numero_voo_volta);
    
    return;
}