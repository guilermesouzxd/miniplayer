#include "lse.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;

struct lse {
    t_elem *inicio;
    int tamanho;
    t_elem *fim;
};

t_lse *lse_criar(void) {
    t_lse *lista = (t_lse *)malloc(sizeof(t_lse));
    if (lista == NULL) return NULL; 
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

int lse_tamanho(const t_lse *lista) {
    assert(lista != NULL);
    return lista->tamanho;
}

void *lse_primeiro(const t_lse *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        return NULL;
    }
    return lista->inicio->carga;
}

t_elem *criar_elem_lse(void *carga) {
    t_elem *novo = malloc(sizeof(t_elem));
    if (novo == NULL) return NULL;
    novo->carga = carga;
    novo->prox = NULL;
    return novo;
}

int lse_inserir_inicio(t_lse *lista, void *carga) {
    if (lista == NULL) return 0;
    t_elem *novo = criar_elem_lse(carga);
    if (novo == NULL) return 0;

    novo->prox = lista->inicio;
    lista->inicio = novo;
    lista->tamanho++;
    return 1;
}

void lse_percorrer(const t_lse *lista, void (*visitar)(void *carga)) {
    if (lista == NULL || visitar == NULL) return;
    t_elem *atual = lista->inicio;
    while (atual != NULL) {
        visitar(atual->carga);
        atual = atual->prox;
    }
}

void lse_destruir(t_lse *lista, void (*destruir)(void *)) {
    if (lista == NULL) return;

    t_elem *atual = lista->inicio;
    while (atual != NULL) {
        t_elem *proximo = atual->prox;
        if (destruir != NULL) {
            destruir(atual->carga);
        }
        free(atual);
        atual = proximo;
    }
    free(lista);
}

int lse_inserir_fim(t_lse *lista, void *carga) {
    if (lista == NULL) return 0;
    t_elem *novo = criar_elem_lse(carga);
    if (novo == NULL) return 0;
    
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        t_elem *cam = lista->inicio;
        while (cam->prox != NULL) {
            cam = cam->prox;
        }
        cam->prox = novo;
    }
    lista->tamanho++;
    return 1;
}

void *lse_remover_inicio(t_lse *lista) {
    assert(lista != NULL);
    if (lista->tamanho == 0) return NULL;  

    t_elem *prim = lista->inicio;
    lista->inicio = prim->prox;
    void *carga = prim->carga;
    free(prim);
    lista->tamanho--;
    return carga;
}

void *lse_buscar(const t_lse *lista, const void *chave, t_comparador comparador) {
    if (lista == NULL || comparador == NULL) return NULL;
    
    t_elem *atual = lista->inicio;
    while (atual != NULL) {
        if (comparador(atual->carga, chave) == 0) {
            return atual->carga;
        }
        atual = atual->prox;
    }
    return NULL;
}

void *lse_remover(t_lse *lista, const void *chave, t_comparador comparador) { 
    if (lista == NULL || comparador == NULL) return NULL;
    
    t_elem *atual = lista->inicio;
    t_elem *anterior = NULL;
    
    while (atual != NULL) {
        if (comparador(atual->carga, chave) == 0) {
            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            void *carga = atual->carga;
            free(atual);
            lista->tamanho--;
            return carga;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return NULL;
}

int lse_inserir_ordenado(t_lse *l, void *c, t_comparador cmp) { 
    (void)l; (void)c; (void)cmp; 
    return 0; 
}   