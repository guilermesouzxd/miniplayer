# Arquitetura
## Componentes
| Módulo | Responsabilidade | Dependências |
|---|---|---|
| musica | Dados da música | biblioteca padrão |
| lse | Nós genéricos e encadeamento | biblioteca padrão |
| pilha | Política LIFO | lse |
| fila | Política FIFO | lse |
| miniplayer | Simulação e integração | demais TADs |

## Diagrama de dependências
MiniPlayer → (LSE, Pilha, Fila) → LSE → t_elem interno.

## Decisões técnicas (preencher)
- Por que `void *`?
- Quem é dono das cargas?
- Como tratar referências compartilhadas?
- Quando adicionar ponteiro `fim`?

---
## M01 — Módulo `musica`
`musica` só depende da biblioteca padrão e não conhece a lista. A música **copia** seus textos (arrays `char[80]`), então não há dono compartilhado de strings.

## M02 — Decisões técnicas (respostas às perguntas acima)
- **Por que `void *`?** Para a lista guardar qualquer tipo (int, `t_musica`…) sem conhecer o tipo; comparações e destruição vêm por callback.
- **Quem é dono das cargas?** Quem as cria. A lista é dona só dos nós. Biblioteca possui as músicas; fila e histórico só as referenciam.
- **Referências compartilhadas:** antes de destruir uma música, removê-la de fila/histórico (ver README).
- **Quando adicionar `fim`?** Não na M04 (`inserir_fim` é O(n)); só como otimização opcional na M08 (fila).
- `t_elem` e `struct lse` ficam em `lse.c`; `lse.h` expõe apenas `t_lse` opaco.

## M03 — Encadeamento
```
lista -> [inicio] --> [carga|prox] --> [carga|prox] --> [carga|NULL]
         tamanho=3
inserir_inicio(X):  novo->prox = inicio;  inicio = novo;  tamanho++
```
`lse_percorrer` oferece iteração por callback sem expor `t_elem`.

## M04 — Ponteiros alterados em cada operação
```
vazia:        inicio=NULL, tamanho=0
um nó:        inicio -> [A|NULL]
três nós:     inicio -> [A] -> [B] -> [C] -> NULL

inserir_fim:      ultimo->prox = novo   (vazia: inicio = novo)
remover cabeça:   inicio = A->prox
remover meio (B): A->prox = B->prox
remover cauda(C): B->prox = NULL        (o anterior passa a ser o último)
remover único:    inicio = NULL, tamanho = 0
```
Em todos os casos: `tamanho--`, `free(nó)`, e a carga é devolvida (não liberada).

