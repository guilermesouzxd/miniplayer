#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "lse.h"
#include "musica.h" 

#define MAX_ESPERADOS 8

static void *esperados[MAX_ESPERADOS];
static int visitas;
static int destruidas;
static void *destruidas_cargas[MAX_ESPERADOS];

static void verificar_ordem(void *carga) {
    assert(visitas < MAX_ESPERADOS);
    assert(carga == esperados[visitas]);
    visitas++;
}

static void conferir(const t_lse *l, int n) {
    assert(lse_tamanho(l) == n);
    visitas = 0;
    lse_percorrer(l, verificar_ordem);
    assert(visitas == n);
}

static void destruir_int(void *carga) {
    assert(destruidas < MAX_ESPERADOS);
    destruidas_cargas[destruidas++] = carga;
    free(carga);
}

static void teste_lista_vazia(void) {
    t_lse *l = lse_criar();
    assert(l != NULL);
    assert(lse_tamanho(l) == 0);
    assert(lse_primeiro(l) == NULL);
    conferir(l, 0); /* percurso sem visitas */
    lse_destruir(l, NULL);
}

static void teste_um_elemento(void) {
    int a = 1;
    t_lse *l = lse_criar();
    assert(l != NULL);
    assert(lse_inserir_inicio(l, &a) == 1);
    assert(lse_primeiro(l) == &a);
    esperados[0] = &a;
    conferir(l, 1);
    lse_destruir(l, NULL);
}

static void teste_encadeamento_e_percurso(void) {
    int a = 1, b = 2, c = 3;
    t_lse *l = lse_criar();
    assert(l != NULL);
    assert(lse_inserir_inicio(l, &a) == 1);
    esperados[0] = &a; conferir(l, 1);
    assert(lse_inserir_inicio(l, &b) == 1);
    esperados[0] = &b; esperados[1] = &a; conferir(l, 2);
    assert(lse_inserir_inicio(l, &c) == 1);
    /* LIFO na cabeca: ordem inversa a insercao */
    esperados[0] = &c; esperados[1] = &b; esperados[2] = &a; conferir(l, 3);
    assert(lse_primeiro(l) == &c);
    lse_destruir(l, NULL);
}

static void teste_carga_generica(void) {
    int n = 7;
    t_musica m1 = {1, "A", "X", 100};
    t_musica m2 = {2, "B", "Y", 200};
    t_lse *li = lse_criar();
    t_lse *lm = lse_criar();
    assert(li != NULL && lm != NULL);

    assert(lse_inserir_inicio(li, &n) == 1);
    esperados[0] = &n; conferir(li, 1);

    assert(lse_inserir_inicio(lm, &m1) == 1);
    assert(lse_inserir_inicio(lm, &m2) == 1);
    esperados[0] = &m2; esperados[1] = &m1; conferir(lm, 2);
    assert(lse_primeiro(lm) == &m2);

    lse_destruir(li, NULL);
    lse_destruir(lm, NULL);
}

static void teste_carga_nula_e_robustez(void) {
    t_lse *l = lse_criar();
    assert(l != NULL);
    assert(lse_inserir_inicio(l, NULL) == 1);
    esperados[0] = NULL; conferir(l, 1);
    assert(lse_primeiro(l) == NULL);
    lse_destruir(l, NULL);

    assert(lse_tamanho(NULL) == 0);
    assert(lse_primeiro(NULL) == NULL);
    lse_percorrer(NULL, verificar_ordem);
    int x = 1;
    t_lse *v = lse_criar();
    assert(v != NULL);
    assert(lse_inserir_inicio(v, &x) == 1);
    lse_percorrer(v, NULL);
    lse_destruir(v, NULL);
    lse_destruir(NULL, NULL);
}

static void teste_destruicao_sem_callback(void) {
    int a = 1, b = 2;
    t_lse *l = lse_criar();
    assert(l != NULL);
    assert(lse_inserir_inicio(l, &a) == 1);
    assert(lse_inserir_inicio(l, &b) == 1);
    lse_destruir(l, NULL);
    assert(a == 1 && b == 2);
}

static void teste_destruicao_com_callback(void) {
    t_lse *l = lse_criar();
    assert(l != NULL);
    int *p[3];
    for (int i = 0; i < 3; i++) {
        p[i] = malloc(sizeof(int));
        assert(p[i] != NULL);
        *p[i] = i;
        assert(lse_inserir_inicio(l, p[i]) == 1);
    }
    destruidas = 0;
    lse_destruir(l, destruir_int);
    assert(destruidas == 3); 
    assert(destruidas_cargas[0] == p[2]);
    assert(destruidas_cargas[1] == p[1]);
    assert(destruidas_cargas[2] == p[0]);
}

int main(void) {
    teste_lista_vazia();
    teste_um_elemento();
    teste_encadeamento_e_percurso();
    teste_carga_generica();
    teste_carga_nula_e_robustez();
    teste_destruicao_sem_callback();
    teste_destruicao_com_callback();
    assert(lse_inserir_inicio(NULL, NULL) == 0);
    puts("M03: todos os testes passaram.");
    return 0;
}
