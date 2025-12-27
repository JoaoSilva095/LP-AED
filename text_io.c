#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void carregar_tudo_do_ficheiro(const char* filename, MATRIX_STR* texto, MATRIX_STR* tokens) {
    if (!filename || !texto || !tokens) return;
    FILE *f = fopen(filename, "r");
    if (!f) return;

    char line[1024];
    const char *delim = " \t\n\r.,;:!-?()\"'";

    while (fgets(line, sizeof(line), f)) {
        /* remover newline/carriage returns */
        size_t len = strlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r')) {
            line[--len] = '\0';
        }
        if (len == 0) continue;

        /* inserir frase no texto apenas se ainda não existir */
        if (procurar_frase(texto, line) == -1) {
            insert_str(texto, line);
        }

        /* tokenizar a linha e inserir tokens únicos */
        char *copy = strdup(line);
        if (!copy) continue;
        char *tok = strtok(copy, delim);
        while (tok) {
            if (procurar_frase(tokens, tok) == -1) {
                insert_str(tokens, tok);
            }
            tok = strtok(NULL, delim);
        }
        free(copy);
    }

    fclose(f);
}
