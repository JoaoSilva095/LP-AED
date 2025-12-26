#ifndef PROJETO_R1_4_H
#define PROJETO_R1_4_H

#include "struct.h"

#define SD_ID -1
#define MAX_OUTPUT 1000

int tokenize_greedy(
    const char *text,
    Token vocab[],
    int vocab_size,
    int output_ids[],
    int max_output);

#endif