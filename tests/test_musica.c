#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "musica.h"
int main(void) {
    t_musica *m = musica_criar(1, "Teste", "Artista", 180);
    assert(m != NULL); 
    assert(m->id == 1 && strcmp(m->titulo, "Teste") == 0);
    assert(strcmp(m->artista, "Artista") == 0);
    assert(m->duracao == 180);
    musica_imprimir(m);
    musica_destruir(m);

    char longo[300];
    memset(longo, 'x', sizeof longo - 1);
    longo[sizeof longo - 1] = '\0';
    t_musica *t = musica_criar(2, longo, longo, 1);
    assert(t != NULL);
    assert(strlen(t->titulo) == MUSICA_TAM_TEXTO - 1);
    assert(strlen(t->artista) == MUSICA_TAM_TEXTO - 1);
    musica_destruir(t);

    assert(musica_criar(3, NULL, "A", 1) == NULL);
    assert(musica_criar(3, "T", NULL, 1) == NULL);
    musica_destruir(NULL);
    musica_imprimir(NULL);

    puts("test_musica: OK");
    return 0;
}
