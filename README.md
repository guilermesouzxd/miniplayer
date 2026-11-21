# MiniPlayer — ICC002 (2026/2)
Projeto integrador progressivo, em duplas, em C. Reprodução **simulada**.

## Estado atual
Concluídas: **M01** (música), **M02–M04** (LSE: criar, tamanho, primeiro, inserir início/fim, percorrer, buscar, remover, remover início, destruir).
Pendentes (stubs): `lse_inserir_ordenado` (M05), pilha (M06), fila (M08), integração (M09).

## Compilação
`make` e `./build/miniplayer`.

## Testes
```bash
make build/test_musica && ./build/test_musica   
make test_m02 test_m03 test_m04               
make test                                       
```

## Contratos
- `void *carga` é genérico; a lista não conhece `t_musica`.
- A lista possui os nós, **não** as cargas, salvo quando `lse_destruir` recebe callback destruidor.
- Remover devolve a carga e libera apenas o nó.
- Pilha e fila reutilizam `lse_*`, sem manipular `t_elem`.
- Biblioteca possui as músicas; histórico e fila só as referenciam.
- Antes de liberar uma música, remover referências a ela de fila e histórico.

## Como documentar
Preencher `docs/arquitetura.md`, `docs/contratos.md`, `docs/diario-de-bordo.md` e `docs/relatorio-testes.md` a cada missão. Ver `GUIA_ESTUDANTE.md`.
