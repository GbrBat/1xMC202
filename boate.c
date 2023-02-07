// Gabriel Batista de Paula 212845
// MC202
// Tarefa 8 - Fila à Brasileira


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Profissoes privilegiadas: 
// coach, ex-bbb, filho-politico, herdeiro, youtuber-financas;
// Outra profissao:
// funcionario

// Estado vacina:
// vacinado, nao-vacinado


typedef struct pessoa *p_pessoa;

struct pessoa {
    int documento;
    char profissao[26];
    char vacina[13];
    p_pessoa prox;
};


p_pessoa criar_lista () {
    return NULL;
}


void limpa_lista (p_pessoa lista) {
    if (lista != NULL) {
        limpa_lista(lista->prox);
        free(lista);
    }
}


int comparar_cargo(char* prof){
    if ((strcmp(prof, "coach") == 0) || (strcmp(prof, "ex-bbb") == 0) || (strcmp(prof, "filho-politico") == 0) 
    || (strcmp(prof, "herdeiro") == 0) || (strcmp(prof, "youtuber-financas") == 0)) {
        return 1;
    } else if (strcmp(prof, "funcionario") == 0) {
        return 0;
    } else if (strcmp(prof, "fiscal") == 0) {
        return 3;
    }
    return 2;
}


int confere_vacina(char* vacina) {
    if (strcmp(vacina, "nao-vacinado") == 0) {
        return 1;
    }
    return 0;
}


void imprime(p_pessoa lista) {
    while(lista) {
        printf("%d %s %s\n", lista->documento, lista->profissao, lista->vacina);
        lista = lista->prox;
    }
}


p_pessoa adiciona_elemento (p_pessoa lista, int doc, char* prof, char* vac, p_pessoa* lanterna) {
    p_pessoa novo, aux, lixo, limpa;
    
    novo = malloc(sizeof (struct pessoa));
    novo->documento = doc;
    strcpy(novo->profissao, prof);
    strcpy(novo->vacina, vac);
    novo->prox = NULL;
    if (comparar_cargo(prof) == 1) {
        novo->prox = lista;
        lista = novo;
        (*lanterna) = novo;
    } else if (comparar_cargo(prof) == 2 || comparar_cargo(prof) == 3) {
        if (lista == NULL) {
            lista = novo;
            (*lanterna) = novo;
        } else {
            aux = lista;
            if (aux != (*lanterna)) {
                while (aux->documento != (*lanterna)->documento || aux->prox != NULL) {
                    if (aux->documento == (*lanterna)->documento) {
                        break;
                    }
                    aux = aux->prox;
                }
            }
            (*lanterna) = novo;
            novo->prox = aux->prox;
            aux->prox = novo;
        }
    } else {
        if (lista == NULL) {
            lista = novo;
            (*lanterna) = novo;
        } else {
            aux = lista;
            while (aux->prox) {
                aux = aux->prox;
            }
            aux->prox = novo;
            (*lanterna) = novo;
        }
    }
    limpa = lista;
    //printf("\n");
    if (limpa->prox != NULL) {
        while(limpa->prox != NULL) {
            if(comparar_cargo(limpa->profissao) == 3) {
                if (confere_vacina(limpa->prox->vacina)){
                    while (confere_vacina(limpa->prox->vacina)){
                        lixo = limpa->prox;
                        limpa->prox = lixo->prox;
                        free(lixo);
                        (*lanterna) = limpa;
                        if (limpa->prox == NULL) {
                            break;
                        }
                    }
                }
            }
            if (limpa->prox != NULL) {
                limpa = limpa->prox;
            }
        }
    }
    return lista;
}


int main(int argc, char const *argv[]) {
    int doc;
    char prof[26];
    char vac[13];
    p_pessoa lanterna = NULL;
    p_pessoa lista;

    lista = criar_lista();

    while (scanf("%d %s %s", &doc, prof, vac) != EOF) {
        lista = adiciona_elemento(lista, doc, prof, vac, &lanterna);
    }
    imprime (lista);
    limpa_lista(lista);
    return 0;
}

