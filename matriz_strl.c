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
//R1.2 Inserir string na matriz
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

MATRIX_INT* create_matrix_int(int capacity) {
    MATRIX_INT* m = (MATRIX_INT*) malloc(sizeof(MATRIX_INT));
    m->data = (int**) malloc(sizeof(int*) * capacity);
    m->rows = 0;
    m->capacity = capacity;
    return m;
}

// Inserir um vetor de inteiros (ex: IDs de tokens de uma frase)
void insert_int_vector(MATRIX_INT* m, int* vector, int length) {
    if (m->rows >= m->capacity) {
        m->capacity *= 2;
        m->data = (int**) realloc(m->data, sizeof(int*) * m->capacity);
    }
    m->data[m->rows] = (int*) malloc(sizeof(int) * (length + 1));
    m->data[m->rows][0] = length; // guarda o tamanho na primeira posição
    for (int i = 0; i < length; i++) {
        m->data[m->rows][i+1] = vector[i];
    }
    m->rows++;
}

// Listar todos os vetores
void list_matrix_int(MATRIX_INT* m) {
    for (int i = 0; i < m->rows; i++) {
        int length = m->data[i][0];
        printf("[%d] -> ", i);
        for (int j = 1; j <= length; j++) {
            printf("%d ", m->data[i][j]);
        }
        printf("\n");
    }
}

// Libertar memória
void free_matrix_int(MATRIX_INT* m) {
    for (int i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

int find_token_id(MATRIX_STR* tokens, const char* word) {
    for (int i = 0; i < tokens->linhas; i++) {
        if (strcmp(tokens->dados[i], word) == 0) {
            return i;
        }
    }
    return -1; // não encontrado
}

// Tokeniza todas as frases do texto
void tokenize_text(MATRIX_STR* texto, MATRIX_STR* tokens, MATRIX_INT* token_ids) {
    for (int i = 0; i < texto->linhas; i++) {
        char* frase = strdup(texto->dados[i]);
        char* token = strtok(frase, " ");
        int ids[100]; // buffer temporário
        int len = 0;

        while (token != NULL) {
            int id = find_token_id(tokens, token);
            if (id != -1) {
                ids[len++] = id;
            }
            token = strtok(NULL, " ");
        }

        insert_int_vector(token_ids, ids, len);
        free(frase);
    }
}

void ler_ficheiro_texto(const char* filename, MATRIX_STR* matriz) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        perror("Erro ao abrir ficheiro");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        // remove \n no fim da linha
        buffer[strcspn(buffer, "\n")] = '\0';
        insert_str(matriz, buffer);
    }

    fclose(f);
}