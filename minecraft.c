// Gabriel Batista de Paula 212845
// MC202
// Tarefa 6 - Minecraft


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minecraft.h"


#define MIN 0
#define MAX 255
#define ALT 256


int **calcularAltitudes(int m, int n, int seed) {
    int **altitudes;
    altitudes = malloc(m * sizeof(Bloco*));
    for (int i = 0; i < m; i++) {
        altitudes[i] = malloc(n * sizeof(Bloco));
        for (int j = 0; j < n; j++) {
            altitudes[i][j] = ((seed * (202 + i + j) + 12345 + i + j) % 256);
        }
    }
    return altitudes;
}


Bloco ***criarMundo(int m, int n, int **altitudes, int seed) {
    int i, j, y;
    Bloco ***mundo;
    mundo = malloc (m * sizeof(Bloco**));
    for (i = 0; i < m; i++) {
        mundo[i] = malloc (n * sizeof(Bloco*));
        for (j = 0; j < n; j++) {
            mundo[i][j] = malloc (256 * sizeof(Bloco));
        }
    }
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            for (y = 0; y < 256; y++) {
                if (altitudes[i][j] < y) {
                    mundo[i][j][y].bloco = 21;
                } else {
                    mundo[i][j][y].bloco = (seed * (202 + i + y + j) + i + y + j) % 33;
                }
            }
        }
    }
    return mundo;
}


double explorarMundo(Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco, int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos) {
    int i, j, y;
    double tempoTotal;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            for (y = 0; y < 256; y++) {
                if (mundo[i][j][y].bloco == 0) {
                    (*qtdDiamante)++;
                    (*qtdBlocos)++;
                } else if (mundo[i][j][y].bloco == 1 || mundo[i][j][y].bloco ==  2) {
                    (*qtdOuro)++;
                    (*qtdBlocos)++;
                } else if (mundo[i][j][y].bloco >= 3 && mundo[i][j][y].bloco <= 5) {
                    (*qtdFerro)++;
                    (*qtdBlocos)++;
                } else if (mundo[i][j][y].bloco >= 6 && mundo[i][j][y].bloco <= 20) {
                    (*qtdBlocos)++;
                } 
            }
        }
    }
    tempoTotal = tempoPorBloco * (*qtdBlocos);
    return tempoTotal;
}


int liberaMundo (Bloco ***mundo, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            free (mundo[i][j]);
        }
        free (mundo[i]);
    }
    free (mundo);
    return 0;
}


int liberaAltitude (int **altitudes, int m) {
    for (int i = 0; i < m; i++) {
        free(altitudes[i]);
    }
    free(altitudes);
    return 0;
}


int main(int argc, char const *argv[])
{
    int m, n, seed, qtdDiamante, qtdOuro, qtdFerro, qtdBlocos, **altitudes;
    double tempoPorBloco, tempoTotal;
    //int a;
    Bloco ***mundo;
    qtdDiamante = 0;
    qtdOuro = 0;
    qtdFerro = 0;
    qtdBlocos = 0;

    scanf("%d %d", &m, &n);
    scanf("%d", &seed);
    scanf("%lf", &tempoPorBloco);

    altitudes = calcularAltitudes(m, n, seed);
    mundo = criarMundo(m, n, altitudes, seed);
    tempoTotal = explorarMundo(mundo, m, n, altitudes, tempoPorBloco, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);

    printf("Total de Blocos: %d\n", qtdBlocos);
    printf("Tempo total: %.2lfs\n", tempoTotal);
    printf("Diamantes: %d\n", qtdDiamante);
    printf("Ouros: %d\n", qtdOuro);
    printf("Ferros: %d\n", qtdFerro);


    /*matriz = malloc (m * sizeof(int**));
    for (i = 0; i < m; i++) {
        matriz[i] = malloc (n * sizeof(int*));
        for (j = 0; j < n; j++) {
            matriz[i][j] = malloc (ALT * sizeof(int));
        }
    }*/
    /*for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            free (matriz[i][j]);
        }
        free (matriz[i]);
    }
    free (matriz);*/
    liberaMundo(mundo, m, n);
    liberaAltitude(altitudes, m);
    /*scanf("%d", &a);
    while (a != 1) {
        scanf("%d", &a);
    }*/
    return 0;
}
