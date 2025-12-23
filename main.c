#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura auxiliar para contar pares
typedef struct {
    char token1[100];
    char token2[100];
    int freq;
} ParFreq;

// Função para encontrar se um par já foi contado
int encontrar_par(ParFreq *lista, int total, char *t1, char *t2) {
    for (int i = 0; i < total; i++) {
        if (strcmp(lista[i].token1, t1) == 0 && strcmp(lista[i].token2, t2) == 0) {
            return i;
        }
    }
    return -1;
}

// R1.3 - Algoritmo de Cálculo do Alfabeto
void executar_R1_3(char ***frase, int *num_tokens_frase, char ***alfabeto, int *num_tokens_alfabeto, int objetivo) {

    while (*num_tokens_alfabeto < objetivo) {
        ParFreq contagem[100]; // Simplificado para o exemplo
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

        // Adicionar ao alfabeto (Matriz Dinâmica) [cite: 139, 154]
        *alfabeto = realloc(*alfabeto, (*num_tokens_alfabeto + 1) * sizeof(char *));
        (*alfabeto)[*num_tokens_alfabeto] = strdup(novo_token);
        (*num_tokens_alfabeto)++;

        // 4. Substituir no texto (Merge)
        // Esta parte encolhe a frase original unindo os dois tokens
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
int main() {
    // Inicialização da frase de teste: "b", "a", "r", " ", "p", "a", "r"
    int num_tokens_frase = 7;
    char **frase = malloc(num_tokens_frase * sizeof(char *));
    frase[0] = strdup("b"); frase[1] = strdup("a"); frase[2] = strdup("r");
    frase[3] = strdup(" "); frase[4] = strdup("p"); frase[5] = strdup("a"); frase[6] = strdup("r");

    // Inicialização do alfabeto de teste: "b", "a", "r", " ", "p"
    int num_tokens_alfabeto = 5;
    char **alfabeto = malloc(num_tokens_alfabeto * sizeof(char *));
    alfabeto[0] = strdup("b"); alfabeto[1] = strdup("a"); alfabeto[2] = strdup("r");
    alfabeto[3] = strdup(" "); alfabeto[4] = strdup("p");

    // Executar o R1.3 até chegar a 7 tokens no alfabeto
    executar_R1_3(&frase, &num_tokens_frase, &alfabeto, &num_tokens_alfabeto, 7);

    // Limpeza
    for(int i=0; i<num_tokens_frase; i++) free(frase[i]);
    free(frase);
    for(int i=0; i<num_tokens_alfabeto; i++) free(alfabeto[i]);
    free(alfabeto);

    return 0;
}