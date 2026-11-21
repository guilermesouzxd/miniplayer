#include "musica.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Copia no maximo tam - 1 caracteres e garante o '\0' final. */
static void copiar_texto(char *destino, size_t tam, const char *origem) {
    strncpy(destino, origem, tam - 1);
    destino[tam - 1] = '\0';
}

t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao) {
    if (titulo == NULL || artista == NULL) {
        return NULL;
    }

    t_musica *nova = malloc(sizeof(t_musica));
    if (nova == NULL) {
        return NULL;
    }

    nova->id = id;
    copiar_texto(nova->titulo, sizeof nova->titulo, titulo);
    copiar_texto(nova->artista, sizeof nova->artista, artista);
    nova->duracao = duracao;

    return nova;
}

void musica_destruir(void *carga) {
    free(carga); /* free(NULL) e seguro: carga NULL e permitida desde a M03. */
}

void musica_imprimir(void *carga) {
    if (carga == NULL) {
        return;
    }
    const t_musica *musica = carga;

    printf("ID: %d \n", musica->id);
    printf("Título: %s \n", musica->titulo);
    printf("Artista: %s \n", musica->artista);
    printf("Duração: %d \n", musica->duracao);
}
