#include "lse.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;

struct lse {
    t_elem *inicio;
    int tamanho;
};

static t_elem *elem_criar(void *carga) {
    t_elem *novo = malloc(sizeof(t_elem));
    if (novo == NULL) {
        return NULL;
    }
    novo->carga = carga;
    novo->prox = NULL;
    return novo;
}

t_lse *lse_criar(void) {
    t_lse *lista = malloc(sizeof(t_lse));
    if (lista == NULL) {
        return NULL;
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

int lse_tamanho(const t_lse *lista) {
    if (lista == NULL) {
        return 0;
    }
    return lista->tamanho;
}

void *lse_primeiro(const t_lse *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        return NULL;
    }
    return lista->inicio->carga;
}

int lse_inserir_inicio(t_lse *lista, void *carga) {
    if (lista == NULL) {
        return 0;
    }
    t_elem *novo = elem_criar(carga);
    if (novo == NULL) {
        return 0;
    }
    novo->prox = lista->inicio;
    lista->inicio = novo;
    lista->tamanho++;
    return 1;
}

int lse_inserir_fim(t_lse *lista, void *carga) {
    if (lista == NULL) {
        return 0;
    }
    t_elem *novo = elem_criar(carga);
    if (novo == NULL) {
        return 0;
    }
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        t_elem *atual = lista->inicio;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }
    lista->tamanho++;
    return 1;
}

void *lse_remover_inicio(t_lse *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        return NULL;
    }
    t_elem *removido = lista->inicio;
    void *carga = removido->carga;
    lista->inicio = removido->prox;
    lista->tamanho--;
    free(removido);
    return carga;
}


void *lse_buscar(const t_lse *lista, const void *chave, t_comparador comparar) {
    if (lista == NULL || comparar == NULL) {
        return NULL;
    }
    for (const t_elem *atual = lista->inicio; atual != NULL; atual = atual->prox) {
        if (comparar(atual->carga, chave) == 0) {
            return atual->carga;
        }
    }
    return NULL;
}


void *lse_remover(t_lse *lista, const void *chave, t_comparador comparar) {
    if (lista == NULL || comparar == NULL) {
        return NULL;
    }
    t_elem *anterior = NULL;
    t_elem *atual = lista->inicio;
    while (atual != NULL) {
        if (comparar(atual->carga, chave) == 0) {
            if (anterior == NULL) {
                lista->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            void *carga = atual->carga;
            lista->tamanho--;
            free(atual);
            return carga;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return NULL;
}


int lse_inserir_ordenado(t_lse *lista, void *carga, t_comparador comparar) {
    (void)lista; (void)carga; (void)comparar;
    return 0;
}


void lse_percorrer(const t_lse *lista, t_lse_visitar visitar) {
    if (lista == NULL || visitar == NULL) {
        return;
    }
    for (const t_elem *atual = lista->inicio; atual != NULL; atual = atual->prox) {
        visitar(atual->carga);
    }
}

void lse_destruir(t_lse *lista, void (*destruir_carga)(void *)) {
    if (lista == NULL) {
        return;
    }
    t_elem *atual = lista->inicio;
    while (atual != NULL) {
        t_elem *proximo = atual->prox;
        if (destruir_carga != NULL) {
            destruir_carga(atual->carga);
        }
        free(atual);
        atual = proximo;
    }
    free(lista);
}
