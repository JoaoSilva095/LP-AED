#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "1.4.h"
#include "1.5.h"

void testar_R1_3() {
    printf("========== TESTE R1.3 - Cálculo do Alfabeto ==========\n");

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

    printf("Alfabeto inicial (%d tokens):\n", num_tokens_alfabeto);
    for(int i=0; i<num_tokens_alfabeto; i++) {
        printf("  [%d]: \"%s\"\n", i, alfabeto[i]);
    }
    printf("\n");

    // Executar o R1.3 até chegar a 7 tokens no alfabeto
    executar_R1_3(&frase, &num_tokens_frase, &alfabeto, &num_tokens_alfabeto, 7);

    printf("\nAlfabeto final (%d tokens):\n", num_tokens_alfabeto);
    for(int i=0; i<num_tokens_alfabeto; i++) {
        printf("  [%d]: \"%s\"\n", i, alfabeto[i]);
    }

    // Limpeza
    for(int i=0; i<num_tokens_frase; i++) free(frase[i]);
    free(frase);
    for(int i=0; i<num_tokens_alfabeto; i++) free(alfabeto[i]);
    free(alfabeto);
}

void testar_R1_4_R1_5() {
    printf("\n\n========== TESTE R1.4 e R1.5 - Tokenização e TF ==========\n");

    // Definição do vocabulário
    Token vocab[] = {
        {"b", 0},
        {"a", 1},
        {"r", 2},
        {" ", 3},
        {"p", 4},
        {"ar", 5},
        {"bar", 6}
    };

    int vocab_size = sizeof(vocab) / sizeof(vocab[0]);

    printf("Vocabulário (%d tokens):\n", vocab_size);
    for(int i=0; i<vocab_size; i++) {
        printf("  Token ID %d: \"%s\"\n", vocab[i].id, vocab[i].token);
    }
    printf("\n");

    // Texto de entrada
    const char *text = "bar par bar a";

    // Tokenização (R1.4)
    int token_ids[MAX_OUTPUT];
    int token_count = tokenize_greedy(text, vocab, vocab_size, token_ids, MAX_OUTPUT);

    printf("Texto: \"%s\"\n", text);
    printf("Vetor de IDs dos tokens: [");
    for (int i = 0; i < token_count; i++) {
        printf("%d", token_ids[i]);
        if (i < token_count - 1) printf(", ");
    }
    printf("]\n\n");

    // Cálculo da TF (R1.5)
    int unique_ids[MAX_TF];
    int tf_values[MAX_TF];
    int unique_count = compute_tf(token_ids, token_count, unique_ids, tf_values);

    printf("Vetorização TF da frase:\n");
    for (int i = 0; i < unique_count; i++) {
        printf("  Token ID %d -> TF = %d\n", unique_ids[i], tf_values[i]);
    }
}

int main() {
    // Testar R1.3
    testar_R1_3();

    // Testar R1.4 e R1.5
    testar_R1_4_R1_5();

    return 0;
}