// Gabriel Batista de Paula 212845
// MC202
// Tarefa 7 - Arranha-Céu


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Verifica se o valor a ser adicionado ja nao aparece na linha ou na coluna especifica
int repete_valor(int **m, int l, int c, int v, int tamanho) {
	int i;
	for (i = 1; i < tamanho+1; i++) 
		if (m[l][i] == v) /* aparece na linha l? */
			return 0;
	for (i = 1; i < tamanho+1; i++)
		if (m[i][c] == v) /* aparece na coluna c? */
			return 0;
	return 1;
}


// Verifica se a visao dos predios eh coerente com os valores tanto horizontais quanto verticais
// Verificacao eh feita utilizando uma variavel iniciada em 1 podendo ter ate o valor "tamanho"
// que se remete ao valor a ser visto dos predios  
int verifica_visao(int **m, int l, int c, int tamanho) {
    int i, j, visaoDir, visaoEsq, visaoCim, visaoBai, maior;
    visaoDir = 1; 
    visaoEsq = 1; 
    visaoCim = 1; 
    visaoBai = 1;
    maior = 0; 

    // Entra nessa condicao caso esteja na ultima coluna, verificando a visao da linha de ambas as
    // extremidades
    if (c == tamanho) {
        maior = m[l][1];
        for (j = 1; j < tamanho; j++) {
            if (maior < m[l][j+1]) {
                visaoEsq++;
                maior = m[l][j+1];
            }
            if (maior == tamanho) {
                break;
            }
        }
        maior = m[l][tamanho];
        for (j = tamanho; j > 1; j--) {
            if (maior < m[l][j-1]) {
                visaoDir++;
                maior = m[l][j-1];
            }
            if (maior == tamanho){
                break;
            }
        }
    }

    // Entra nessa condicao caso esteja na ultima linha, verificando a visao da coluna de ambas as
    // extremidades
    if (l == tamanho) {
        maior = m[1][c];
        for (i = 1; i+1 < tamanho+1; i++) {
            if (maior < m[i+1][c]) {
                visaoCim++;
                maior = m[i+1][c];
            }
            if (maior == tamanho){
                break;
            }
        }
        maior = m[tamanho][c];
        for (i = tamanho; i-1 > 0; i--) {
            if (maior < m[i-1][c]) {
                visaoBai++;
                maior = m[i-1][c];
            }
            if (maior == tamanho){
                break;
            }
        }
    }
    if (l == tamanho && c == tamanho) {
        return visaoEsq == m[l][0] && visaoDir == m[l][tamanho+1] && visaoCim == m[0][c] && visaoBai == m[tamanho+1][c];
    } else if (c == tamanho) {
        return visaoEsq == m[l][0] && visaoDir == m[l][tamanho+1];
    } else if (l == tamanho) {
        return visaoCim == m[0][c] && visaoBai == m[tamanho+1][c];
    }
    return 0;
}


void proxima_posicao(int l, int c, int *nl, int *nc, int tamanho) {
	if (c < tamanho) {
		*nl = l;
		*nc = c+1;
	} else {
		*nl = l+1;
		*nc = 1;
	}
}


void imprimi_arranhaceu(int **m, int tamanho){
    int  i, j;
    for (i = 1; i < tamanho+1; i++){
        for (j = 1; j < tamanho+1; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}


int arranhaceuR(int **m, int l, int c, int tamanho) {
	int v, nl, nc;
	if (l > tamanho) {
		imprimi_arranhaceu(m, tamanho);
		return 1;
	}
	proxima_posicao(l, c, &nl, &nc, tamanho);
	for (v = 1; v < tamanho+1; v++) {
		if (repete_valor(m, l, c, v, tamanho)) {
			m[l][c] = v;
			if(c == tamanho || l == tamanho) {
                if (verifica_visao(m, l, c, tamanho)) {
                    if (arranhaceuR(m, nl, nc, tamanho)) {
                        return 1;
                    }
                } else {
                    m[l][c] = 0;
                    return 0;
                }
            } 
            if(arranhaceuR(m, nl, nc, tamanho)) {
                return 1;    
            }
		}
	}
	m[l][c] = 0;
	return 0;
}


int main(int argc, char const *argv[])
{
    int tamanho, i, j, **matriz;
    
    scanf("%d", &tamanho);

    matriz = malloc((tamanho+2) * sizeof(int*));    
    for (i = 0; i < (tamanho+2); i++) {
        matriz[i] = malloc((tamanho+2) * sizeof(int));
    }


    for (i = 0; i < (tamanho+2); i++) {
        for (j = 0; j < (tamanho+2); j++) {
            scanf("%d", &matriz[i][j]);            
        }
    }

    arranhaceuR(matriz, 1, 1, tamanho);


    for (i = 0; i < (tamanho+2); i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}