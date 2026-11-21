# Diário de bordo

## Missão M01 — 11/11
- Integrantes e papéis: Caio Sam e Guilherme Oliveira
- Objetivo: Desenvolvimento de um mini player de música utilizando conceitos de estruturas de dados dinâmicas.
- O que implementamos: `musica_criar` e `musica_destruir`, e `musica_imprimir` (pedida pelo professor ao final da aula).
- Decisão técnica e justificativa: a função de impressão foi requisitada pelo professor. Na revisão final, a cópia de strings passou de `strcpy` para cópia truncada com `'\0'` garantido (o kit pedia "cópia segura de strings"), e `musica_destruir` passou a aceitar `NULL`.
- Problema encontrado e solução: `musica.c` usava `assert`, `strcpy` e `printf` sem os `#include` correspondentes (não linkava); corrigido com `<assert.h>`/`<string.h>`/`<stdio.h>`. `musica_imprimir` não estava declarada em `musica.h`; declarada.
- Evidências de testes: `tests/test_musica.c` passa, inclusive com ASan/UBSan.
- Próxima ação: M02.

## Missão M02 — 13/11
- Integrantes e papéis: [preencher: quem codificou / quem revisou]
- Objetivo: lista vazia (`lse_criar`, `lse_tamanho`, `lse_primeiro`, `lse_destruir`).
- O que implementamos: as quatro funções em `src/lse.c`.
- Decisão técnica: `lse_tamanho(NULL)` devolve 0 em vez de abortar com `assert` (um `assert` some com `-DNDEBUG`; devolver 0 é consistente com `lse_primeiro(NULL)`).
- Problema encontrado e solução: o `lse.c` entregue tinha assinaturas sem `const` diferentes de `lse.h` (erro "conflicting types"), `lse_destruir` declarada como `void *` sem retornar valor, `lse_criar` deixava um campo `fim` não inicializado, e `lse_inserir_inicio` estava definida duas vezes. Corrigido alinhando ao `.h` e removendo o `fim` (a M04 proíbe o ponteiro `fim`).
- Evidências de testes: antes — `make -f missoes/M02/Makefile.incremental test_m02` não compilava; depois — "M02: teste de contrato passou."
- Próxima ação: M03.

## Missão M03 — 16/11
- Integrantes e papéis: [preencher: quem codificou / quem revisou — alternar em relação à M02]
- Objetivo: inserção no início, percurso por callback e destruição com destrutor opcional.
- O que implementamos: `lse_inserir_inicio` (com verificação de `lista == NULL` e de `malloc`), `lse_percorrer`, `lse_destruir` completo; testes de `missoes/M03/test_m03.c` (os `assert(1==0)` do modelo foram substituídos por testes reais).
- Decisão técnica: carga `NULL` é permitida (um nó ainda é um nó), com a ambiguidade documentada em `contratos.md`.
- Problema encontrado e solução: o enunciado declara `typedef ... t_lse_visitar` mas usa `t_visitar` no protótipo. Mantivemos `t_lse_visitar` e adicionamos `typedef t_lse_visitar t_visitar;` para aceitar os dois nomes. Também havia `lse_inserir_inicio` duplicada (stub de M04 sobrando), removida.
- Evidências de testes: "M03: todos os testes passaram."; ASan/UBSan sem erros.
- Quem libera o quê: a lista libera os nós; a carga é do chamador (ou do destrutor, se informado).
- Próxima ação: M04.

## Missão M04 — 18/11
- Integrantes e papéis: [preencher: quem codificou / quem revisou]
- Objetivo: `lse_inserir_fim`, `lse_buscar`, `lse_remover`, `lse_remover_inicio`.
- O que implementamos: as quatro operações sem ponteiro `fim` (inserção O(n)); testes completos em `missoes/M04/test_m04.c`, incluindo chave duplicada, remoção de único elemento e reinserção.
- Decisão técnica: `lse_remover` usa ponteiro `anterior` e remove só a primeira ocorrência; libera só o nó.
- Problema encontrado e solução: `test_m04.c` usava `t_musica` sem declará-lo, embora definisse `musica_t` localmente; trocamos o uso para `musica_t` (mantém o teste da lista independente de `musica.h`). As asserções originais foram mantidas.
- Evidências de testes: M02, M03, M04 e `tests/test_lse.c` passam; também com `-Werror`, ASan e UBSan. Mutações no código (esquecer `tamanho--`, não religar `anterior->prox`) são detectadas pelo teste da M04.
- Próxima ação: M05 (`lse_inserir_ordenado`, ainda stub).
