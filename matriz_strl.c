#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

MATRIX_STR* criar_matriz(int capacidade) {
    MATRIX_STR* matriz = malloc(sizeof(MATRIX_STR));
    matriz->dados = malloc(capacidade * sizeof(char*));
    matriz->linhas = 0;
    matriz->capacidade = capacidade;
    return matriz;
}

void insert_str(MATRIX_STR* matriz, const char* str) {
    if (matriz->linhas >= matriz->capacidade) {
        matriz->capacidade *= 2;
        matriz->dados = realloc(matriz->dados,
                                matriz->capacidade * sizeof(char*));
    }
    matriz->dados[matriz->linhas] = strdup(str);
    matriz->linhas++;
}

void lista_da_matriz(MATRIX_STR* matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        printf("%s\n", matriz->dados[i]);
    }
}

void ler_ficheiro_texto(const char* filename, MATRIX_STR* matriz) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        buffer[strcspn(buffer, "\n")] = '\0';
        insert_str(matriz, buffer);
    }

    fclose(f);
}

void guardar_ficheiro_texto(const char* filename, MATRIX_STR* matriz) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Erro ao escrever ficheiro");
        return;
    }

    for (int i = 0; i < matriz->linhas; i++) {
        fprintf(f, "%s\n", matriz->dados[i]);
    }

    fclose(f);
}

int procurar_frase(MATRIX_STR* matriz, const char* frase) {
    for (int i = 0; i < matriz->linhas; i++) {
        if (strcmp(matriz->dados[i], frase) == 0) {
            return i;
        }
    }
    return -1;
}

int procurar_substring(MATRIX_STR* matriz, const char* sub) {
    for (int i = 0; i < matriz->linhas; i++) {
        if (strstr(matriz->dados[i], sub)) {
            return i;
        }
    }
    return -1;
}

int remover_frase(MATRIX_STR* matriz, const char* frase) {
    int pos = procurar_frase(matriz, frase);
    if (pos == -1) return 0;

    free(matriz->dados[pos]);

    for (int i = pos; i < matriz->linhas - 1; i++) {
        matriz->dados[i] = matriz->dados[i + 1];
    }

    matriz->linhas--;
    return 1;
}

void libertar_matriz(MATRIX_STR* matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        free(matriz->dados[i]);
    }
    free(matriz->dados);
    free(matriz);
}

MATRIX_INT* create_matrix_int(int capacity) {
    MATRIX_INT* m = malloc(sizeof(MATRIX_INT));
    m->data = malloc(sizeof(int*) * capacity);
    m->rows = 0;
    m->capacity = capacity;
    return m;
}

void insert_int_vector(MATRIX_INT* m, int* vector, int length) {
    if (m->rows >= m->capacity) {
        m->capacity *= 2;
        m->data = realloc(m->data, sizeof(int*) * m->capacity);
    }

    m->data[m->rows] = malloc(sizeof(int) * (length + 1));
    m->data[m->rows][0] = length;

    for (int i = 0; i < length; i++) {
        m->data[m->rows][i + 1] = vector[i];
    }

    m->rows++;
}

void list_matrix_int(MATRIX_INT* m) {
    for (int i = 0; i < m->rows; i++) {
        int len = m->data[i][0];
        printf("[%d] -> ", i);
        for (int j = 1; j <= len; j++) {
            printf("%d ", m->data[i][j]);
        }
        printf("\n");
    }
}

void free_matrix_int(MATRIX_INT* m) {
    for (int i = 0; i < m->rows; i++) {
        free(m->data[i]);
    }
    free(m->data);
    free(m);
}

int find_token_id(MATRIX_STR* tokens, const char* word) {
    for (int i = 0; i < tokens->linhas; i++) {
        if (strcmp(tokens->dados[i], word) == 0)
            return i;
    }
    return -1;
}

void tokenize_text(MATRIX_STR* texto, MATRIX_STR* tokens, MATRIX_INT* token_ids) {
    for (int i = 0; i < texto->linhas; i++) {
        char* frase = strdup(texto->dados[i]);
        char* token = strtok(frase, " ");

        int ids[100];
        int len = 0;

        while (token) {
            int id = find_token_id(tokens, token);
            if (id != -1) ids[len++] = id;
            token = strtok(NULL, " ");
        }

        insert_int_vector(token_ids, ids, len);
        free(frase);
    }
}
