#ifndef PROJETO_MAIN_H
#define PROJETO_MAIN_H

typedef struct {
    char **dados;
    int linhas;
    int capacidade;
} MATRIX_STR;

MATRIX_STR* criar_matriz(int capacidade);
void insert_str(MATRIX_STR* matriz, const char* str);
void lista_da_matriz(MATRIX_STR* matriz);
void ler_ficheiro_texto(const char* filename, MATRIX_STR* matriz);
void guardar_ficheiro_texto(const char* filename, MATRIX_STR* matriz);
int procurar_frase(MATRIX_STR* matriz, const char* frase);
int procurar_substring(MATRIX_STR* matriz, const char* sub);
int remover_frase(MATRIX_STR* matriz, const char* frase);
void libertar_matriz(MATRIX_STR* matriz);

/* -------- MATRIZ DE INTEIROS -------- */

typedef struct {
    int **data;
    int rows;
    int capacity;
} MATRIX_INT;

MATRIX_INT* create_matrix_int(int capacity);
void insert_int_vector(MATRIX_INT* m, int* vector, int length);
void list_matrix_int(MATRIX_INT* m);
void free_matrix_int(MATRIX_INT* m);

int find_token_id(MATRIX_STR* tokens, const char* word);
void tokenize_text(MATRIX_STR* texto, MATRIX_STR* tokens, MATRIX_INT* token_ids);

#endif
