#ifndef MUSICA_H
#define MUSICA_H

#define MUSICA_TAM_TEXTO 80

typedef struct musica {
    int id;
    char titulo[MUSICA_TAM_TEXTO];
    char artista[MUSICA_TAM_TEXTO];
    int duracao;
} t_musica;


t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao);

void musica_destruir(void *carga);

void musica_imprimir(void *carga);

#endif
