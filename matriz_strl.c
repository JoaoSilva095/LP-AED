#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"


MATRIX_STR* criar_matriz(int capacidade) {
    MATRIX_STR *matriz;// apontador da struct
    matriz = (MATRIX_STR *)malloc(sizeof(MATRIX_STR));
    matriz->dados = (char **)malloc(capacidade * sizeof(char *)); // cria espaço para os apontadores de char
    matriz->linhas = 0;
    matriz->capacidade = capacidade;
    return matriz;


}
void insert_str(MATRIX_STR* matriz, const char* str) {
    if (matriz->linhas >= matriz->capacidade) {
        matriz->capacidade *= 2; // Multiplica o tamanho da capacidade
        matriz->dados = (char**) realloc(matriz->dados, matriz->capacidade * sizeof(char*));
        //Pede mais memória para matriz e atualiza o apontador
    }
    // Duplica e insere a string
    matriz->dados[matriz->linhas] = strdup(str); // strdup aloca memória e copia a string
    matriz->linhas++;
}
void lista_da_matriz(MATRIX_STR *matriz) {
    if (matriz == NULL || matriz->dados == NULL) {
        printf("Matriz já foi libertada.\n");
        return;
    }
    for (int i = 0; i < matriz->linhas; i++) {
        printf("%s\n", matriz->dados[i]);
    }
}

void libertar_matriz(MATRIX_STR* matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        free(matriz->dados[i]); // Liberta cada string individualmente
    }
    free(matriz->dados); // Liberta o array de apontadores
    free(matriz); // Liberta a struct

}
