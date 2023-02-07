// Gabriel Batista de Paula 212845
// MC202
// Tarefa 9 - Seleção de equipes


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct jogador *p_jogador;

struct jogador {
    int altura;
    p_jogador anterior;
    p_jogador proximo;
};


p_jogador criaLista() {
    return NULL;
}


void imprimeLista(p_jogador lista) {
    p_jogador atual;
    atual = lista->proximo;
    do {
        printf("%d ", atual->altura);
        atual = atual->proximo;
    } while (atual != lista->proximo);
}


p_jogador insereJogador(p_jogador lista, int alt) {
    p_jogador aux, novo;
    novo = malloc(sizeof(struct jogador));
    novo->altura = alt;
    novo->anterior = NULL;
    novo->proximo = NULL;
    if(lista == NULL) {
        novo->anterior = novo;
        novo->proximo = novo;
        lista = novo;
    } else {
        aux = lista->proximo;
        novo->proximo = lista->proximo;
        novo->anterior = lista;
        lista->proximo = novo;
        aux->anterior = novo;
    }
    return novo;
}


p_jogador insereOrdenado(p_jogador equipe, int alt) {
    p_jogador aux, novo;
    novo = malloc(sizeof(struct jogador));
    novo->altura = alt;
    novo->anterior = NULL;
    novo->proximo = NULL;
    if (novo) {
        if (equipe == NULL) {
            novo->anterior = novo;
            novo->proximo = novo;
            equipe = novo;
        } else if (novo->altura <= equipe->proximo->altura) {
            novo->proximo = equipe->proximo;
            novo->anterior = equipe;
            equipe->proximo->anterior = novo;
            equipe->proximo = novo;
        } else {
            aux = equipe->proximo->proximo;
            while (aux != equipe->proximo && novo->altura > aux->altura) {
                aux = aux->proximo;
            }
            if (aux->altura == equipe->proximo->altura) {
                novo->proximo = equipe->proximo;
                novo->anterior = equipe;
                equipe->proximo = novo;
                aux->anterior = novo;
                equipe = novo;
            } else {
                novo->proximo = aux;
                novo->anterior = aux->anterior;
                aux->anterior->proximo = novo;
                aux->anterior = novo;
            }
        }
    }
    return equipe;
}


p_jogador insereEquipe (p_jogador lista, p_jogador equipe, int dado, int count) {
    p_jogador aux;
    int i;
    aux = lista->proximo;	
    if (count%2 == 0) {
        for (i = 1; i < dado; i++) {
            aux = aux->proximo;
        }
    } else {
        for (i = 1; i < dado; i++) {
            aux = aux->anterior;
        }
    }
    equipe = insereOrdenado(equipe, aux->altura);
    return equipe;
}

p_jogador removeJogador(p_jogador lista, int dado, int count) {
    p_jogador aux, lixo;
    int i;
    aux = lista->proximo;
    if (count%2 == 0) {
        for (i = 1; i < dado; i++) {
            aux = aux->proximo;
        }
    } else {
        for (i = 1; i < dado; i++) {
            aux = aux->anterior;
        }
    }
    if (aux == lista) {
        lista->anterior->proximo = aux->proximo;
        lista->proximo->anterior = aux->anterior;
        lista = lista->anterior;
        free(aux);
    } else {
        lixo = aux;
        aux->anterior->proximo = aux->proximo;
        aux->proximo->anterior = aux->anterior;
        aux = lixo->anterior;
        free(lixo);
    }
    return lista;
}


void limpa_lista (p_jogador lista) {
    p_jogador aux, prox;
    aux = lista->proximo;
    while (aux != lista) {
        prox = aux->proximo;
        free(aux);
        aux = prox;
    }
}


int main(int argc, char const *argv[]) {
    p_jogador lista, equipe_um, equipe_dois;
    int n, count, alt, dado;

    lista = criaLista();
    equipe_um = criaLista();
    equipe_dois = criaLista();
    count = 0;
    
    scanf("%d", &n);
    while (count < n) {
        scanf("%d", &alt);
        lista = insereJogador(lista, alt);
        count++;
    }
    count = 1;
    while (count <= n) {
        scanf("%d", &dado);
        if (count%2 == 1) {
            equipe_um = insereEquipe(lista, equipe_um, dado, count);
            lista = removeJogador(lista, dado, count);
        } else {
            equipe_dois = insereEquipe(lista, equipe_dois, dado, count);
            lista = removeJogador(lista, dado, count);
        }
        count++;
    }
    imprimeLista(equipe_um);
    printf("\n");
    imprimeLista(equipe_dois);

    limpa_lista(lista);
    limpa_lista(equipe_um);
    limpa_lista(equipe_dois);
    
    return 0;
}

