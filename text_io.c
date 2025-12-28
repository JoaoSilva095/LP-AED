#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void carregar_tudo_do_ficheiro(const char* filename, MATRIX_STR* texto, MATRIX_STR* tokens) {
    if (!filename || !texto || !tokens) return; // Este IF basicamente verifica se o ficheiro existe e se o texto e tokens são validos
    FILE *f = fopen(filename, "r");
    if (!f) return; // se o ficheiro não abrir , fecha. Isto foi Tip do AI :)

    char line[1024]; // line: buffer onde cada linha do ficheiro é lida ou seja uma zona de memoria reservada temporaria
    const char *delim = " \t\n\r.,;:!-?()\"'"; // para delimitar estes caracters para nao ser considerados tokens

    while (fgets(line, sizeof(line), f)) {
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
