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

    int pos = procurar_frase(texto, "the cat sleeps");
    if (pos != -1) {
        printf("Frase 'the cat sleeps' encontrada na posicao: %d\n", pos);
    } else {
        printf("Frase 'the cat sleeps' nao encontrada.\n");
    }

    int pos_sub = procurar_substring(texto , "dog");
    if (pos_sub != -1) {
        printf("Substring 'cat' encontrada na posicao: %d\n", pos_sub);
    } else {
        printf("Substring 'cat' nao encontrada.\n");
    }

  if (remover_frase(texto , "the dog runs")) {
        printf("Frase 'a dog runs' removida com sucesso.\n");
    } else {
        printf("Frase 'a dog runs' nao encontrada para remocao.\n");
    }

    printf("\n frase depois de remover \n");
    lista_da_matriz(texto);

    free_matrix_int(token_ids);
    libertar_matriz(tokens);
    libertar_matriz(texto);
    return 0;
}