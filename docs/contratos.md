# Contratos dos TADs
Para **cada função**, preencher:
- Nome e assinatura:
- Pré-condições:
- Pós-condições:
- Valor de retorno em sucesso/falha:
- Quem aloca/libera a memória:
- Invariantes preservadas:
- Testes associados:

## Invariantes da LSE
- `tamanho >= 0`.
- `tamanho == 0` se e somente se `inicio == NULL`.
- Há exatamente `tamanho` nós alcançáveis a partir de `inicio`.
- O último nó aponta para `NULL` e não há ciclos.

---
## M01 — TAD Música (`musica.h` / `musica.c`)
### `t_musica *musica_criar(int id, const char *titulo, const char *artista, int duracao)`
- Pré-condições: nenhuma sobre `id`/`duracao`; `titulo` e `artista` devem ser strings terminadas em `'\0'`.
- Pós-condições: campos preenchidos; textos **copiados** (a música não referencia as strings do chamador), truncados em 79 caracteres e sempre terminados em `'\0'`.
- Retorno: ponteiro novo; `NULL` se `titulo`/`artista` forem `NULL` ou faltar memória.
- Memória: aloca com `malloc`; **o chamador é dono** e deve chamar `musica_destruir`.
- Testes: `tests/test_musica.c` (T01–T04).
### `void musica_destruir(void *carga)`
- Pré: `carga` veio de `musica_criar` ou é `NULL`. Pós: memória liberada. `NULL` é aceito (nada acontece), pois a carga `NULL` é permitida desde a M03 e esta função é usada como callback de `lse_destruir`.
### `void musica_imprimir(void *carga)`
- Imprime id, título, artista e duração em `stdout`; não faz nada se `carga == NULL`. Não altera nem libera a música.

## M02 — Lista vazia (`lse_criar`, `lse_tamanho`, `lse_primeiro`, `lse_destruir`)
- `lse_criar()`: devolve lista vazia (`inicio == NULL`, `tamanho == 0`) ou `NULL` se `malloc` falhar. Memória: aloca só a estrutura `t_lse`.
- `lse_tamanho(lista)`: 0 em lista vazia. **Decisão:** `lista == NULL` devolve 0 (consistente com `lse_primeiro(NULL) == NULL`; não aborta).
- `lse_primeiro(lista)`: `NULL` se a lista for `NULL` ou vazia.
- `lse_destruir(lista, destruir_carga)`: em lista vazia só libera a estrutura; `lista == NULL` não faz nada.
- Invariantes: as da seção "Invariantes da LSE" acima; `t_elem` e `struct lse` continuam privados a `lse.c`.
- Testes: `missoes/M02/TESTE_INCREMENTAL_M02.c`.

## M03 — Inserção no início, percurso e destruição
- `int lse_inserir_inicio(lista, carga)`: novo nó aponta para o antigo `inicio`; `inicio` passa a ser o novo nó; `tamanho++`. Retorna 1 (sucesso) ou 0 (`lista == NULL` ou falta de memória; a lista fica intacta). Custo O(1).
- **Decisão sobre carga `NULL`:** é permitida (um nó ainda é um nó). Consequência: `lse_primeiro` devolve `NULL` tanto para lista vazia quanto para primeiro nó com carga `NULL`; use `lse_tamanho` para distinguir.
- `void lse_percorrer(lista, visitar)`: chama `visitar(carga)` do início ao fim, uma vez por nó; não faz nada se `lista` ou `visitar` forem `NULL` ou se a lista estiver vazia. O callback **não deve** inserir/remover nós da lista durante o percurso.
- `void lse_destruir(lista, destruir_carga)`: libera todos os nós e a lista. Se `destruir_carga != NULL`, chama-a **uma vez por carga, antes de liberar o nó** (o ponteiro `prox` é salvo antes do `free`). Com `NULL`, as cargas não são tocadas (podem ser variáveis automáticas).
- **Quem libera o quê:** a lista libera **nós**; a **carga** é do chamador, exceto se ele passar o destrutor.
- Tipos: `t_lse_visitar` (alias `t_visitar`, nome usado no enunciado).
- Testes: `missoes/M03/test_m03.c`.

## M04 — Inserção no fim, busca e remoção
- `int lse_inserir_fim(lista, carga)`: percorre até o último nó (O(n), sem ponteiro `fim`) e liga o novo nó; em lista vazia equivale a `inserir_inicio`. Retorna 1/0 como acima.
- `void *lse_buscar(lista, chave, comparar)`: primeira carga com `comparar(carga, chave) == 0`; `NULL` se não encontrar ou se `lista`/`comparar` forem `NULL`. Não altera a lista.
- `void *lse_remover(lista, chave, comparar)`: remove só o **primeiro** nó correspondente, religa o anterior (ou `inicio`), `tamanho--`, libera **apenas o nó** e devolve a carga; `NULL` se não encontrar/argumento inválido.
- `void *lse_remover_inicio(lista)`: remove o primeiro nó e devolve a carga; `NULL` se lista `NULL` ou vazia.
- `comparar` não pode alterar carga nem chave. Para músicas, compara-se por `id` **fora** de `lse.c` (a lista não conhece `t_musica`). Tipo: `t_comparador` (alias `t_comparador_lse`).
- **Ambiguidade do `NULL`:** como `NULL` também significa "não encontrado/vazio", cargas `NULL` não devem ser usadas em busca/remoção. Uma API futura poderia devolver o status por valor de retorno (`int`) e a carga por parâmetro de saída (`void **out`), ou usar um nó sentinela.
- Invariantes preservadas em todas as operações: `tamanho == nós alcançáveis`, último `prox == NULL`, `tamanho == 0 ⇔ inicio == NULL`.
- Testes: `missoes/M04/test_m04.c`; regressão com M02/M03 e `tests/test_lse.c`.

