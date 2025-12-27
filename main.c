#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "1.4.h"
#include "1.5.h"


void testar_R1_2() {
    printf("========== TESTE R1.2 - Manipulação de Texto ==========\n\n");

    // Criar matriz para texto
    MATRIX_STR* texto = criar_matriz(3);


    // Tentar ler do ficheiro (se existir)
    ler_ficheiro_texto("Frases.txt", texto);

    // Se não houver ficheiro, adicionar frases manualmente
    if (texto->linhas == 0) {
        printf("Ficheiro 'Frases.txt' não encontrado. Usando dados de teste.\n");
        insert_str(texto, "the cat sleeps");
        insert_str(texto, "the dog runs");
        insert_str(texto, "a cat eats");
    }

    printf("Frases carregadas:\n");
    lista_da_matriz(texto);

    // Criar tokens
    MATRIX_STR* tokens = criar_matriz(3);
    carregar_tudo_do_ficheiro("Frases.txt", texto, tokens);


    printf("\nTokens disponíveis:\n");
    lista_da_matriz(tokens);


    MATRIX_INT* token_ids = create_matrix_int(3):

    printf("\nTokenização das frases:\n");
    list_matrix_int(token_ids);

    printf("========== TOKENS DISPONIVEIS  ==========\n");
    for (int i = 0; i < tokens->linhas; i++) {
        printf("ID %d: %s\n", i, tokens->dados[i]);
    }

    // 4. Executar a Tokenização (Transformar frases em IDs)

    tokenize_text(texto, tokens, token_ids);

    // 5. Mostrar o resultado da Tokenização
    printf("\n========== TOKENIZACAO DAS FRASES (VETORES DE IDS) ==========\n");
    list_matrix_int(token_ids);


    // Procurar frase
    int pos = procurar_frase(texto, "the cat sleeps");
    if (pos != -1) {
        printf("\nFrase 'the cat sleeps' encontrada na posição: %d\n", pos);
    } else {
        printf("\nFrase 'the cat sleeps' não encontrada.\n");
    }

    // Procurar substring
    int pos_sub = procurar_substring(texto, "dog");
    if (pos_sub != -1) {
        printf("Substring 'dog' encontrada na posição: %d\n", pos_sub);
    } else {
        printf("Substring 'dog' não encontrada.\n");
    }

    // Remover frase
    if (remover_frase(texto, "the dog runs")) {
        printf("Frase 'the dog runs' removida com sucesso.\n");
    } else {
        printf("Frase 'the dog runs' não encontrada para remoção.\n");
    }

    printf("\nFrases após remoção:\n");
    lista_da_matriz(texto);

    // Limpeza
    free_matrix_int(token_ids);
    libertar_matriz(tokens);
    libertar_matriz(texto);
}

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
    // Testar R1.2
    testar_R1_2();
    // Testar R1.3
    testar_R1_3();

    // Testar R1.4 e R1.5
    testar_R1_4_R1_5();

    return 0;
}