#include <stdio.h>
#include <stdlib.h>
#include "struct.h"

void guardar_texto_txt(const char *filename, MATRIX_STR *texto) {
    if (!filename || !texto) return;

    FILE *f = fopen(filename, "w");
    if (!f) return;

    for (int i = 0; i < texto->linhas; i++) {
        fprintf(f, "%s\n", texto->dados[i]);
    }

    fclose(f);
}

void guardar_tokens_txt(const char *filename, MATRIX_STR *tokens) {
    if (!filename || !tokens) return;

    FILE *f = fopen(filename, "w");
    if (!f) return;

    for (int i = 0; i < tokens->linhas; i++) {
        fprintf(f, "%d %s\n", i, tokens->dados[i]);
    }

    fclose(f);
}

void guardar_tf_txt(const char *filename, Token_List *lista) {
    if (!filename || !lista) return;

    FILE *f = fopen(filename, "w");
    if (!f) return;

    Token_Node *atual = lista->head;
    int frase = 0;

    while (atual) {
        fprintf(f, "S%d: ", frase);
        for (int i = 0; i < atual->tam_vetores; i++) {
            fprintf(f, "%d:%d ",
                    atual->token_ids[i],
                    atual->t_valores[i]);
        }
        fprintf(f, "\n");

        atual = atual->next;
        frase++;
    }

    fclose(f);
}
void teste_R2_3(DOC *doc) {
    guardar_texto_txt("texto.txt", doc->texto);
    guardar_tokens_txt("tokens.txt", doc->tokens);
    guardar_tf_txt("tf.txt", doc->tf_list);
}