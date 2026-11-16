#include "musica.h"
#include <stddef.h>
#include <stdlib.h>
/* M01: substituir stubs por alocacao, copia segura de strings e free. */
t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao) {
    
    t_musica * nova = malloc(sizeof(t_musica));

    if (nova == NULL) {
        return NULL;
    }

    nova->id = id;
    strcpy(nova->titulo, titulo);
    strcpy(nova->artista, artista);
    nova->duracao = duracao;

    return nova;
}
void musica_destruir(void *carga) { 
    
    assert(carga != NULL);

    free((t_musica *)carga);
}

void musica_imprimir(void *carga) {
    t_musica *musica = (t_musica *)carga;

    printf("ID: %d \n", musica->id);
    printf("Nome: %s \n", musica->titulo);
    printf("Artista: %s \n", musica->artista);
    printf("Duração: %d \n", musica->duracao);
}
