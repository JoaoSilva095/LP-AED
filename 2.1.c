#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

/**
 * R2.1 - Inicializa uma lista duplamente ligada vazia.
 */
Token_List* criar_lista() {
    Token_List* lista = (Token_List*)malloc(sizeof(Token_List));
    if (lista == NULL) return NULL;

    lista->head = NULL;
    lista->tail = NULL;
    lista->total_tokens = 0;
    return lista;
}

/**
 * R2.1 - Insere um novo nó no fim da lista com os vetores de uma frase.
 */
void inserir_no_fim(Token_List* lista, int *ids, int *tfs, int tam) {
    if (lista == NULL) return;

    Token_Node* novo = (Token_Node*)malloc(sizeof(Token_Node));
    if (novo == NULL) return;

    // Alocação e cópia profunda dos vetores (Deep Copy)
    novo->token_ids = (int*)malloc(tam * sizeof(int));
    novo->t_valores = (int*)malloc(tam * sizeof(int));

    if (novo->token_ids && novo->t_valores) {
        memcpy(novo->token_ids, ids, tam * sizeof(int));
        memcpy(novo->t_valores, tfs, tam * sizeof(int));
    }

    novo->tam_vetores = tam;
    novo->next = NULL;
    novo->prev = lista->tail;

    // Ajuste dos apontadores da lista
    if (lista->head == NULL) {
        lista->head = novo; // Primeiro nó da lista
    } else {
        lista->tail->next = novo; // Liga o antigo último ao novo
    }

    lista->tail = novo; // O novo nó passa a ser o rabo da lista
    lista->total_tokens++;
}

/**
 * R2.1 - Percorre a lista e imprime os dados guardados.
 */
void listar_tokens(Token_List* lista) {
    if (lista == NULL || lista->head == NULL) {
        printf("A lista esta vazia.\n");
        return;
    }

    Token_Node* atual = lista->head;
    int i = 0;
    printf("\n--- LISTAGEM DE VETORES (LISTA LIGADA R2.1) ---\n");
    while (atual != NULL) {
        printf("Frase %d (Tam: %d): ", i++, atual->tam_vetores);
        for (int j = 0; j < atual->tam_vetores; j++) {
            printf("[%d:%d] ", atual->token_ids[j], atual->t_valores[j]);
        }
        printf("\n");
        atual = atual->next;
    }
}
void libertar_lista(Token_List* lista) {
    if (lista == NULL) return;

    Token_Node* atual = lista->head;
    while (atual != NULL) {
        Token_Node* proximo = atual->next;
        //Libertar o que está dentro do nó
        free(atual->token_ids);
        free(atual->t_valores);

        // Libertar o nó
        free(atual);

        atual = proximo;
    }
    /**
 * R2.1 - Retorna o apontador para o nó numa determinada posição.
 * Útil para aceder aos dados de uma frase específica sem percorrer a lista manualmente no main.
 */
    Token_Node* obter_no_posicao(Token_List* lista, int pos) {
        if (lista == NULL || pos < 0 || pos >= lista->total_tokens) {
            return NULL;
        }

        Token_Node* atual = lista->head;
        for (int i = 0; i < pos; i++) {
            if (atual == NULL) return NULL;
            atual = atual->next;
        }
        return atual;
    }

    /**
     * R2.1 - Remove um nó da lista numa determinada posição (0 a N-1).
     * Importante para manter a lista sincronizada se apagares uma frase do texto.
     */
    int remover_no_posicao(Token_List* lista, int pos) {
        if (lista == NULL || pos < 0 || pos >= lista->total_tokens) {
            printf("Erro: Posicao de remocao invalida.\n");
            return 0;
        }

        Token_Node* alvo = lista->head;

        // 1. Navegar até ao nó na posição desejada
        for (int i = 0; i < pos; i++) {
            alvo = alvo->next;
        }

        // 2. Ajustar os ponteiros dos nós vizinhos (Lógica de Lista Duplamente Ligada)
        if (alvo->prev != NULL) {
            alvo->prev->next = alvo->next;
        } else {
            lista->head = alvo->next; // O nó era a cabeça
        }

        if (alvo->next != NULL) {
            alvo->next->prev = alvo->prev;
        } else {
            lista->tail = alvo->prev; // O nó era a cauda
        }

        // 3. Libertar a memória interna do nó (os 3 mallocs que falámos)
        free(alvo->token_ids);
        free(alvo->t_valores);
        free(alvo);

        lista->total_tokens--;
        return 1;
    }
    // Libertar a estrutura de controlo
    free(lista);
}