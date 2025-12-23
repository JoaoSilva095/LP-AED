#include <stdio.h>
#include "1.4.h"
#include "1.5.h"

int main() {
    //Definição do vocabulário

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

    //Texto de entrada

    const char *text = "bar par bar a";//mudar a(s) palavra(s) para oq quiserermos, irá ser a palavra q os ids irão procurar, caso n exista aparece -1 na letra

    //Tokenização
    int token_ids[MAX_OUTPUT];

    int token_count = tokenize_greedy(
        text,
        vocab,
        vocab_size,
        token_ids,
        MAX_OUTPUT
    );

    printf("Texto: \"%s\"\n", text);
    printf("Vetor de IDs dos tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("%d ", token_ids[i]);
    }
    printf("\n\n");

    //Cálculo da TF

    int unique_ids[MAX_TF];
    int tf_values[MAX_TF];

    int unique_count = compute_tf(
        token_ids,
        token_count,
        unique_ids,
        tf_values
    );

    printf("Vetorização TF da frase:\n");
    for (int i = 0; i < unique_count; i++) {
        printf("Token ID %d -> TF = %d\n",
               unique_ids[i],
               tf_values[i]);
    }

    return 0;
}
