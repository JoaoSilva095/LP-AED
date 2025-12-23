#include <string.h>
#include "1.4.h"

int tokenize_greedy(
    const char *text,
    Token vocab[],
    int vocab_size,
    int output_ids[],
    int max_output
) {
    int pos = 0;
    int out_len = 0;
    int text_len = strlen(text);

    while (pos < text_len && out_len < max_output) {
        int best_match_len = 0;
        int best_match_id = SD_ID;

        // Procurar o token mais longo que casa nesta posição
        for (int i = 0; i < vocab_size; i++) {
            int token_len = strlen(vocab[i].token);

            if (token_len > best_match_len &&
                strncmp(&text[pos], vocab[i].token, token_len) == 0) {
                best_match_len = token_len;
                best_match_id = vocab[i].id;
                }
        }

        if (best_match_len > 0) {
            output_ids[out_len++] = best_match_id;// token encontrado
            pos += best_match_len;
        } else {
            output_ids[out_len++] = SD_ID;//se nenhum token foi encontrado
            pos += 1;
        }
    }

    return out_len;
}
