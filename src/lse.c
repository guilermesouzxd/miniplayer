#include "lse.h"
#include <stddef.h>
#include <stdlib.h>

/* Representacao interna: NAO mover para lse.h. */
typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;

struct lse {
    t_elem *inicio;
    int tamanho;
    /* Sem ponteiro fim na M04 (inserir_fim e O(n)); ver M08 (opcional). */
};

/* Aloca um no isolado. Devolve NULL em falha de memoria. */
static t_elem *elem_criar(void *carga) {
    t_elem *novo = malloc(sizeof(t_elem));
    if (novo == NULL) {
        return NULL;
    }
    novo->carga = carga;
    novo->prox = NULL;
    return novo;
}

/* M02: lista vazia alocada, ou NULL em falha de memoria. */
t_lse *lse_criar(void) {
    t_lse *lista = malloc(sizeof(t_lse));
    if (lista == NULL) {
        return NULL;
    }
    lista->inicio = NULL;
    lista->tamanho = 0;
    return lista;
}

/* M02/M03: numero de nos; 0 para lista NULL (ver docs/contratos.md). */
int lse_tamanho(const t_lse *lista) {
    if (lista == NULL) {
        return 0;
    }
    return lista->tamanho;
}

/* M02/M03: carga do primeiro no, ou NULL se a lista for NULL ou vazia. */
void *lse_primeiro(const t_lse *lista) {
    if (lista == NULL || lista->inicio == NULL) {
        return NULL;
    }
    return lista->inicio->carga;
}

/* M03: o novo no aponta para o antigo primeiro. Carga NULL e permitida. */
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

/* M04: percorre ate o ultimo no (O(n)) e liga o novo no depois dele. */
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

/* M04: libera so o no e devolve a carga (quem libera a carga e o dono dela). */
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

/* M04: primeira carga com comparar(carga, chave) == 0; nao altera a lista. */
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

/* M04: remove so o PRIMEIRO no correspondente; libera o no, devolve a carga. */
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

/* TODO M05 */
int lse_inserir_ordenado(t_lse *lista, void *carga, t_comparador comparar) {
    (void)lista; (void)carga; (void)comparar;
    return 0;
}

/* M03: visita as cargas do inicio ao fim. Nao faz nada se lista/visitar NULL. */
void lse_percorrer(const t_lse *lista, t_lse_visitar visitar) {
    if (lista == NULL || visitar == NULL) {
        return;
    }
    for (const t_elem *atual = lista->inicio; atual != NULL; atual = atual->prox) {
        visitar(atual->carga);
    }
}

/* M03: libera todos os nos e a lista. Se destruir_carga != NULL, chama-a uma
 * vez por carga ANTES de liberar o no. O proximo e guardado antes do free. */
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
