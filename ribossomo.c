// Gabriel Batista de Paula 212845
// MC202
// Tarefa 5 - Ribossomo alienígena


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[]) {
    char dna[27], rna[27];
    char *seguimentos;
    char *transcricao;
    char *id;
    int n, cont, cond;

    cond = 0;
    fflush(stdin);
    scanf("%s", dna);
    scanf("%s", rna);
    int count;
    count = strlen(rna);
    scanf("%d", &n);
    seguimentos = malloc((n+1)*sizeof(char));
    scanf("%s", seguimentos);
    transcricao = malloc((n+1)*sizeof(char));

    // Nesse trecho a transcricao eh realizada, comparando o "valor" do 
    // seguimento com o "valor" do dna, caso sejam os mesmos, a transcricao
    // recebe o "valor" de rna na posicao do dna correspondente 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < count; j++) {
            if (seguimentos[i] == dna[j]) {
                transcricao[i] = rna[j];
                break;
            } else {
                continue;
            }
        }
    }

    // O ID eh feito de forma unica, para em seguida ser impresso
    // O programa compara o primeiro termo do vetor "transcricao" com todos
    // os seguintes, caso seja igual, o vetor ID vai receber o numero de cada
    // repeticao na posicao em que os elementos estao no vetor "transcricao"
    // Para os termos seguintes, o programa inicialmente compara com os termos
    // anteriores.
    // Caso o termo ja tenha sido utilizado anteriormente, a variavel condicional
    // "cond" recebe o valor '1', impedindo que o programa avance para a parte
    // dos ID e nao tenha o problema de escrever um dado em cima do outro
    id = malloc((n+1)*sizeof(char));
    for (int a = 0; a < n; a++) {
        cont = 0;
        for (int c = a; c-1 >= 0; c--) {
            if (transcricao[a] == transcricao[c-1]) {
                cond = 1;
                break;
            }
        }
        if (cond == 0) {
            for (int b = a; b < n; b++) {
                if (transcricao[a] == transcricao[b]) {
                    id[b] = cont;
                    cont++;
                }
            }    
        }
        cond = 0;
    }

    printf("ID:\t");
    for (int m = 0; m < n; m++) {
        printf("%d\t", id[m]);
    }
    printf("\n");

    printf("DNA:\t");
    for (int j = 0; j < n; j++) {
        printf("%c\t", seguimentos[j]);
    }
    printf("\n");

    printf("\t");
    for (int k = 0; k < n; k++) {
        printf("|\t");
    }
    printf("\n");

    printf("RNA:\t");
    for (int l = 0; l < n; l++) {
        printf("%c\t", transcricao[l]);
    }
    
    free(seguimentos);
    free(transcricao);
    free(id);

    return 0;
}