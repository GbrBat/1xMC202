#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "planejar.h"

void registrar(int i, Voo *voos, int num_voo, char* cod_origem, char* cod_destino, Data data, float valor){
    voos[i].num_voo = num_voo;
    strcpy(voos[i].cod_origem,cod_origem); 
    strcpy(voos[i].cod_destino,cod_destino); 
    voos[i].data = data;
    voos[i].valor = valor;
};

Data ler_data(char *data){
    Data data1;
    char aux[4];
    aux[0] = '\0';
    for (int i = 0; i < 2; i++) {
        aux[i] = data[i];
    }
    data1.dia = atoi(aux);
    aux[0] = '\0';
    int j = 0;
    for (int i = 3; i < 5; i++) {
        aux[j] = data[i];
        j++;
    }
    data1.mes = atoi(aux);
    aux[0] = '\0';
    j = 0;
    for (int i = 6; i < 10; i ++) {
        aux[j] = data[i];
        j++;
    }
    data1.ano = atoi(aux);
    aux[0] = '\0';
    memset(aux, '\0', 4);
    return data1;
}

void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor) {
    for (int i = 0; i < qtd_voos; i++) {
        if (voos[i].num_voo == numero_voo) {
            voos[i].valor = novo_valor;
            break;
        }
    }
};

void cancelar(Voo voos[], int qtd_voos, int numero_voo) {
    for (int i = 0; i < qtd_voos; i++) {
        if (voos[i].num_voo == numero_voo) {
            for (int j = i; j < qtd_voos-1; j++) {
                voos[j] = voos[j+1];
                qtd_voos--;
            }
        }
    }
};

int compara_data(Data data1, Data data2) {
    if (data1.mes == data2.mes) {
        if ((data2.dia - data1.dia) >= 0) {
            return 1;
        } else {
            return 0;
        }
    } else if (data1.mes > data2.mes) {
        if (data1.ano < data2.ano) {
            return 1;
        } else {
            return 0;
        }
        
    } else {
        if (data1.ano == data2.ano) {
            return 1;
        } else {
            return 0;
        }
    }
};

int diferenca_data(Data data1, Data data2) {
    int num_dias = 0;
    if (data1.mes == data2.mes) {
        if ((data2.dia - data1.dia) >= 3) {
            return 1;
        } else {
            return 0;
        }
    } else if (data1.mes < data2.mes) {
        if (data1.mes == 1 || data1.mes == 3 || data1.mes == 5 || data1.mes == 7 || data1.mes == 8 || data1.mes == 10 || data1.mes == 12) {
            num_dias = 31;
            num_dias += data2.dia;
            if ((num_dias - data1.dia) >= 3) {
                return 1;
            } else {
                return 0;
            }
        } else if (data1.mes == 2) {
            num_dias = 28;
            num_dias += data2.dia;
            if ((num_dias - data1.dia) >= 3) {
                return 1;
            } else {
                return 0;
            }
        } else {
            num_dias = 30;
            num_dias += data2.dia;
            if ((num_dias - data1.dia) >= 3) {
                return 1;
            } else {
                return 0;
            }
        }
    } else {
        num_dias = 31;
        num_dias += data2.dia;
        if ((num_dias - data1.dia) >= 3) {
            return 1;
        } else {
            return 0;
        }
    }
};

void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[]) {
    //printf("Quantidade de voos: %d\n", qtd_voos);
    Voo voos_disp[100];
    Voo voos_volta[100];
    float preco;
    int j = 0;
    int l = 0;
    Voo voo_ida;
    Voo voo_volta;
    for (int i = 0; i < qtd_voos; i++) {
        if (strcmp(voos[i].cod_origem,codigo_origem) == 0) {
            if (compara_data(data_inicio, voos[i].data) == 1 && diferenca_data(voos[i].data, data_fim) == 1) {
                voos_disp[j] = voos[i];
                j++;
            }
        }
    }
    preco = voos_disp[0].valor;
    for (int k = 0; k < j; k++) {
        if (voos_disp[k].valor < preco) {
            preco = voos_disp[k].valor;
            l = k;
        }
    }
    voo_ida = voos_disp[l];


    j = 0;
    l = 0;
    for (int x = 0; x < qtd_voos; x++) {
        if (strcmp(voos[x].cod_destino, voo_ida.cod_origem) == 0 && strcmp(voos[x].cod_origem,voo_ida.cod_destino) == 0) {
            if (compara_data(voos[x].data, data_fim) == 1 && diferenca_data(voo_ida.data, voos[x].data) == 1) {
                voos_volta[j] = voos[x];
                //printf("Valor de X volta: %d\n", x);
                //printf("Codigo do voos: %d\n", voos_volta[j]);
                j++;
            }
        }
    }
    preco = voos_volta[0].valor;
    for (int k = 0; k < j; k++) {
        if (voos_volta[k].valor < preco) {
            preco = voos_volta[k].valor;
            l = k;
        }
    }
    voo_volta = voos_volta[l];

    printf("%d\n", voo_ida.num_voo);
    printf("%d\n", voo_volta.num_voo);
};