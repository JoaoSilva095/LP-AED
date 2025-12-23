#ifndef LPAED_TEST_1_4_H
#define LPAED_TEST_1_4_H

#define SD_ID -1        // ID do símbolo desconhecido
#define MAX_OUTPUT 1000

typedef struct {
    const char *token;
    int id;
} Token;

int tokenize_greedy(
    const char *text,
    Token vocab[],
    int vocab_size,
    int output_ids[],
    int max_output
);

#endif
