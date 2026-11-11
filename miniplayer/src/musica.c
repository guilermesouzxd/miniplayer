#include "musica.h"
#include <stddef.h>

/* M01: substituir stubs por alocacao, copia segura de strings e free. */

t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao) {

    (int)id; (char*)titulo; (char*)artista; (int)duracao;
    
    return NULL; 
}

void musica_destruir(void *carga) { 
/* TODO M01 */ 

(void*)carga;

}

