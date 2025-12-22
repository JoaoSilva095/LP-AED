#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"


int main(void) {
    MATRIX_STR* texto = criar_matriz(3);
    ler_ficheiro_texto("C:/Users/Rafael/CLionProjects/projeto/Frases.txt", texto);
    printf("Frase guardadas do ficheiro:\n");
    lista_da_matriz(texto);
    MATRIX_STR* tokens = criar_matriz(8);
    insert_str(tokens, "the");
    insert_str(tokens, "a");
    insert_str(tokens, "cat");
    insert_str(tokens, "dog");
    insert_str(tokens, "sleeps");
    insert_str(tokens, "runs");
    insert_str(tokens, "eats");

    MATRIX_INT* token_ids = create_matrix_int(3);

    tokenize_text(texto, tokens, token_ids);

    list_matrix_int(token_ids);

    free_matrix_int(token_ids);
    libertar_matriz(tokens);
    libertar_matriz(texto);
    return 0;
}