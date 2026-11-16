#include "../include/musica.h"
#include <stdio.h>

typedef struct no{
void *carga;
struct no *prox;
} t_no;

typedef struct lista{
t_no *inicio;
int tamanho;
} t_lse;

t_lse *lse_criar(void){
  t_lse *lista = (t_lse *)malloc(sizeof(t_lse));
  if(lista == NULL){
    return NULL;
  }
  lista->inicio = NULL;
  lista->tamanho = 0;
  return lista;
}
