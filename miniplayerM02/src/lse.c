#include "lse.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
/* Representacao interna: NAO mover para lse.h. */
typedef struct elem {
    void *carga;
    struct elem *prox;
} t_elem;
struct lse {
    t_elem *inicio;
    int tamanho;
    /* M08 (otimizacao opcional): t_elem *fim; */
};
/* Stubs intencionalmente incompletos; testes devem falhar ate implementacao. */

t_lse *lse_criar(void) {
    
    t_lse * lista = (t_lse *)malloc(sizeof(t_lse));

    if (lista == NULL){
        return NULL; 
    }

    lista->inicio = NULL;
    lista->tamanho = 0;

    return lista;
} /* TODO M02/M03 */

int lse_tamanho(t_lse *lista) {
    assert (lista != NULL);

    return lista->tamanho;
}

void *lse_primeiro(t_lse *lista) {
    if (lista == NULL || lista->inicio == NULL){
        return NULL;
    }

    return lista->inicio->carga;
}

t_elem *criar_elem_lse(void * carga){
    
    t_elem *novo = malloc(sizeof(t_elem));

    novo->carga = carga;
    novo->prox = NULL;

    return novo;
}

int lse_inserir_inicio(t_lse * lista, void * carga){

    t_elem * novo = criar_elem_lse(carga);

    if (lista->inicio == NULL) {
        lista->inicio = novo;
    }else {
        novo->prox = lista->inicio;
        lista->inicio = novo;
    }

    lista->tamanho++;
    return 1;
}

void *lse_destruir(t_lse *lista, void (*destruir)(void *)) {

    (void)destruir;

    if (lista == NULL){

        return;
    }

    free(lista);
}






int lse_inserir_inicio(t_lse *l, void *c) { (void)l; (void)c; return 0; } /* TODO M04 */
int lse_inserir_fim(t_lse *l, void *c) { (void)l; (void)c; return 0; } /* TODO M04 */
void *lse_remover_inicio(t_lse *l) { (void)l; return NULL; } /* TODO M04 */
void *lse_buscar(const t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
void *lse_remover(t_lse *l, const void *ch, t_comparador cmp) { (void)l; (void)ch; (void)cmp; return NULL; } /* TODO M04 */
int lse_inserir_ordenado(t_lse *l, void *c, t_comparador cmp) { (void)l; (void)c; (void)cmp; return 0; } /* TODO M05 */
