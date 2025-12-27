#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int encontrar_par(ParFreq *lista, int total, char *t1, char *t2) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].token1, t1) == 0 && strcmp(lista[i].token2, t2) == 0) {
            return i;
        }
    }
    return -1;
}

void executar_R1_3(char ***frase, int *num_tokens_frase, char ***alfabeto, int *num_tokens_alfabeto, int objetivo) {

    while (*num_tokens_alfabeto < objetivo) {
        ParFreq contagem[100];
        int total_pares = 0;

        // 1. Contar frequências de pares consecutivos
        for (int i = 0; i < *num_tokens_frase - 1; i++) {
            char *t1 = (*frase)[i];
            char *t2 = (*frase)[i+1];

            int idx = encontrar_par(contagem, total_pares, t1, t2);
            if (idx != -1) {
                contagem[idx].freq++;
            } else {
                strcpy(contagem[total_pares].token1, t1);
                strcpy(contagem[total_pares].token2, t2);
                contagem[total_pares].freq = 1;
                total_pares++;
            }
        }

        // 2. Escolher o par mais frequente
        if (total_pares == 0) break;
        int max_idx = 0;
        for (int i = 1; i < total_pares; i++) {
            if (contagem[i].freq > contagem[max_idx].freq) max_idx = i;
        }

        // 3. Criar o novo token fundido
        char novo_token[200];
        sprintf(novo_token, "%s%s", contagem[max_idx].token1, contagem[max_idx].token2);

        // Adicionar ao alfabeto
        *alfabeto = realloc(*alfabeto, (*num_tokens_alfabeto + 1) * sizeof(char *));
        (*alfabeto)[*num_tokens_alfabeto] = strdup(novo_token);
        (*num_tokens_alfabeto)++;

        // 4. Substituir no texto (Merge)
        for (int i = 0; i < *num_tokens_frase - 1; i++) {
            if (strcmp((*frase)[i], contagem[max_idx].token1) == 0 &&
                strcmp((*frase)[i+1], contagem[max_idx].token2) == 0) {

                free((*frase)[i]);
                free((*frase)[i+1]);
                (*frase)[i] = strdup(novo_token);

                // Puxar o resto da matriz para a esquerda
                for (int j = i + 1; j < *num_tokens_frase - 1; j++) {
                    (*frase)[j] = (*frase)[j+1];
                }
                (*num_tokens_frase)--;
            }
        }
        printf("Novo Token Criado: '%s' (ID: %d)\n", novo_token, *num_tokens_alfabeto - 1);
    }
}
