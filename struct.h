//
// Created by Rafael on 22/11/2025.
//
#ifndef PROJETO_MAIN_H
#define PROJETO_MAIN_H


typedef struct {
    char **dados;   // matriz de strings ou seja um apontador para apontadores de char
    int linhas;
    int capacidade;  // capacidade máxima
} MATRIX_STR;


// Funções para manipular a matriz de strings.

MATRIX_STR* criar_matriz(int capacidade);

// Insere uma string na matriz, redimensionando se necessário.
void insert_str(MATRIX_STR* matriz, const char* str);

// Da ao utilizador a lista de strings na matriz.
void lista_da_matriz(MATRIX_STR *matriz);

void libertar_matriz(MATRIX_STR* matriz);


// Tokens ???

typedef struct {
    int **data;     // matriz de inteiros (cada linha = vetor de IDs)
    int rows;       // número de linhas ocupadas
    int capacity;   // capacidade máxima de linhas
} MATRIX_INT;

MATRIX_INT* create_matrix_int(int capacity);
void insert_int_vector(MATRIX_INT* m, int* vector, int length);
void list_matrix_int(MATRIX_INT* m);
void free_matrix_int(MATRIX_INT* m);

int find_token_id(MATRIX_STR* tokens, const char* word);
// Tokeniza todas as frases do texto
void tokenize_text(MATRIX_STR* texto, MATRIX_STR* tokens, MATRIX_INT* token_ids);
//ler o ficheiro texto e guardar na matriz
void ler_ficheiro_texto(const char* filename, MATRIX_STR* matriz);


#endif //PROJETO_MAIN_H