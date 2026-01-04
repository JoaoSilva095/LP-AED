#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
// ==========================================
// PARTE 1: Estrutura DOC (Agregadora) - R2.2
// ==========================================

// Cria a estrutura que junta tudo: Texto, Tokens, IDs e a Lista TF
DOC* criar_documento() {
    DOC* doc = (DOC*) malloc(sizeof(DOC));

    // Inicializa todas as sub-estruturas
    doc->texto = criar_matriz(10);          // Para as frases
    doc->tokens = criar_matriz(50);         // Para o vocabulário
    doc->token_ids = create_matrix_int(10); // Para os IDs
    doc->tf_list = criar_lista();           // Para a lista ligada (R2.1)

    return doc;
}

// Liberta a memória de TODAS as estruturas de uma vez
void libertar_documento(DOC* doc) {
    if (!doc) return;

    // Chama as funções de limpeza de cada módulo
    libertar_matriz(doc->texto);
    libertar_matriz(doc->tokens);
    free_matrix_int(doc->token_ids);

    // AQUI é que precisávamos daquela linha no struct.h!
    libertar_lista(doc->tf_list);

    free(doc);
}

// ==========================================
// PARTE 2: Similaridade de Jaccard - R2.2
// ==========================================

// Fórmula: Jaccard = (Interseção) / (União)
// Interseção: nº de tokens que existem nas duas frases
// União: total de tokens únicos nas duas frases (sem repetir)
float calcular_jaccard(int idsA[], int tamA, int idsB[], int tamB) {
    // Casos especiais para evitar divisão por zero
    if (tamA == 0 && tamB == 0) return 1.0;
    if (tamA == 0 || tamB == 0) return 0.0;

    int intersecao = 0;

    // Conta quantos IDs da frase A também estão na frase B
    for (int i = 0; i < tamA; i++) {
        for (int j = 0; j < tamB; j++) {
            if (idsA[i] == idsB[j]) {
                intersecao++;
                break; // Passa para o próximo token de A
            }
        }
    }

    // Matemática de Conjuntos: |A U B| = |A| + |B| - |A n B|
    int uniao = tamA + tamB - intersecao;

    if (uniao == 0) return 0.0;

    return (float)intersecao / (float)uniao;
}