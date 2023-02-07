// Gabriel Batista de Paula 212845
// MC202
// Tarefa 4 - Planejamento de viagem


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planejar.h"


#define MAX 100


int main()
{
    int num, qtd_voos = 0;
    char cod_ini[4], cod_fim[4];
    float valor;
    Voo voos[MAX];
    Data data1, data2, data3;
    char acao[9], data[10], data_aux[10];
    scanf("%s", acao);
    while (strcmp(acao, "planejar") != 0) {
        if (strcmp(acao, "registrar") == 0) {
            fflush(stdin);
            scanf("%d %s %s %s %f", &num, cod_ini, cod_fim, data, &valor);
            data1 = ler_data(data);
            registrar(qtd_voos, voos, num, cod_ini, cod_fim, data1, valor);
            qtd_voos++;
        } else if (strcmp(acao, "alterar") == 0) {
            fflush(stdin);
            scanf("%d %f", &num, &valor);
            alterar(voos, qtd_voos, num, valor);
        } else if (strcmp(acao, "cancelar") == 0) {
            fflush(stdin);
            scanf("%d", &num);
            cancelar(voos, qtd_voos, num);
            qtd_voos--;
        } 
        scanf("%s", acao);
    }
    fflush(stdin);
    scanf("%s", cod_ini);
    fflush(stdin);
    scanf("%s %s", data, data_aux);
    data2 = ler_data(data);
    data3 = ler_data(data_aux);
    planejar(voos, qtd_voos, data2, data3, cod_ini);
    int w;
    scanf("%d", &w);
    return 0;
}