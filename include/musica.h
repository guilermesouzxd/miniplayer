#ifndef MUSICA_H
#define MUSICA_H

#define MUSICA_TAM_TEXTO 80

typedef struct musica {
    int id;
    char titulo[MUSICA_TAM_TEXTO];
    char artista[MUSICA_TAM_TEXTO];
    int duracao;
} t_musica;

/* M01: aloca e preenche uma musica. Copia titulo e artista (truncando em
 * MUSICA_TAM_TEXTO - 1 caracteres, sempre terminados em '\0').
 * Retorna NULL em falha (titulo/artista NULL ou sem memoria). */
t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao);

/* M01: libera uma musica. Aceita NULL (nao faz nada). Assinatura void * para
 * servir de callback em lse_destruir. */
void musica_destruir(void *carga);

/* M01: imprime os campos da musica em stdout. Nao faz nada se carga == NULL. */
void musica_imprimir(void *carga);

#endif
