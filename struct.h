//
// Created by Rafael on 22/11/2025.
//

#ifndef PROJETO_MAIN_H
#define PROJETO_MAIN_H


typedef struct {
    char **dados;   // matriz de strings ou seja um apontador para apontadores de char
    int linhas;
    int capacidade;  // capacidade máxima
    int ids;
} MATRIX_STR;


// Funções para manipular a matriz de strings.

MATRIX_STR* criar_matriz(int capacidade);

// Insere uma string na matriz, redimensionando se necessário.
void insert_str(MATRIX_STR* matriz, const char* str);

// Da ao utilizador a lista de strings na matriz.
void lista_da_matriz(MATRIX_STR *matriz);


#endif //PROJETO_MAIN_H
