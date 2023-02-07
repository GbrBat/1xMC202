#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct voo {
    int num_voo;
    char cod_origem[4];
    char cod_destino[4];
    Data data;
    float valor;
} Voo;

Data ler_data(char *data);

Data valida_data(Data data1);

int compara_data(Data data_ferias, Data data_voo);

int diferenca_data(Data data1, Data data2);

void cancelar(Voo voos[], int qtd_voos, int numero_voo);

void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor);

void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[]);

void registrar(int i, Voo voos[], int num_voo, char* cod_origem, char* cod_destino, Data data, float valor);