# Relatório de testes
| ID | Missão | Função/contrato | Entrada/cenário | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|---|---|
| T01 | M01 | musica_criar | dados válidos | ponteiro não nulo e campos corretos | idêntico ao esperado | ok |
| T02 | M01 | musica_criar | título/artista com 299 caracteres | truncado em 79 e terminado em `\0` | `strlen == 79` | ok |
| T03 | M01 | musica_criar | título ou artista `NULL` | `NULL` | `NULL` | ok |
| T04 | M01 | musica_destruir / imprimir | `NULL` | sem efeito, sem falha | sem falha | ok |
| T05 | M02 | lse_criar/tamanho/primeiro/destruir | lista recém-criada | tamanho 0, primeiro `NULL` | idêntico | ok |
| T06 | M03 | lse_inserir_inicio + percurso | 1 e 3 elementos | ordem inversa à inserção (LIFO) | idêntico | ok |
| T07 | M03 | carga genérica | `int` e `t_musica` | percurso correto | idêntico | ok |
| T08 | M03 | lse_inserir_inicio | lista `NULL`; carga `NULL` | 0; 1 e `tamanho == 1` | idêntico | ok |
| T09 | M03 | lse_percorrer | lista `NULL`, callback `NULL`, vazia | nenhuma visita, sem falha | idêntico | ok |
| T10 | M03 | lse_destruir | sem callback (cargas automáticas) | cargas intactas | idêntico | ok |
| T11 | M03 | lse_destruir | com callback, 3 cargas no heap | 3 chamadas, uma por carga | idêntico | ok |
| T12 | M04 | lse_inserir_fim | lista vazia e não vazia | ordem de inserção preservada | idêntico | ok |
| T13 | M04 | lse_buscar | primeiro/meio/último/ausente | carga ou `NULL`; lista inalterada | idêntico | ok |
| T14 | M04 | lse_remover | cabeça, meio, cauda, único | nó religado, `tamanho` correto | idêntico | ok |
| T15 | M04 | lse_remover | chave duplicada; inexistente | só a 1ª ocorrência; `NULL` | idêntico | ok |
| T16 | M04 | lse_remover_inicio | vazia, `NULL`, com elementos | `NULL` / cargas em ordem | idêntico | ok |
| T17 | M04 | remoção + reinserção | esvaziar e reinserir | lista consistente | idêntico | ok |
| T18 | M04 | args. inválidos | lista/callback `NULL` | `0`/`NULL`, sem acesso inválido | idêntico | ok |
| T19 | M04 | lse_destruir após remoções | callback contador | só cargas presentes destruídas | 2 chamadas | ok |

## Casos-limite
- Estrutura vazia: T05, T09, T16.
- Estrutura com um elemento: T06, T14, T16, T17.
- Chave inexistente: T13, T15.
- Falha de alocação: tratada no código (`elem_criar`/`lse_criar` devolvem `NULL`, as inserções devolvem 0 sem alterar a lista). Não há teste automatizado; uma estratégia seria um `malloc` "envolvido" por macro nos testes, a discutir.

## Memória
Compilação: `gcc -std=c11 -Wall -Wextra -Wpedantic -Werror -g -Iinclude -fsanitize=address,undefined`.
Ferramentas: AddressSanitizer e UndefinedBehaviorSanitizer (sem vazamentos nem acessos inválidos nos testes M02/M03/M04, `test_lse` e `test_musica`).
Comandos: `make test_m02 test_m03 test_m04`, `make build/test_musica && ./build/test_musica`.
Problemas corrigidos: ver `docs/diario-de-bordo.md` (M01–M04).
`make test` ainda falha em `test_pilha`/`test_fila`: esperado, são stubs das missões M06 e M08.

## Estado dos testes antes da correção (como entregue)
- `make build/test_musica`: não linkava (`assert` sem `#include <assert.h>`).
- M02, M03, M04: `src/lse.c` não compilava (conflitos de tipo e redefinição).
