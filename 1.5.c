#include "1.5.h"


int compute_tf(
    int token_ids[],
    int token_count,
    int unique_ids[],
    int tf_values[]
) {
    int unique_count = 0;

    for (int i = 0; i < token_count; i++) {
        int id = token_ids[i];
        int found = 0;

        // Verificar se o ID já existe
        for (int j = 0; j < unique_count; j++) {
            if (unique_ids[j] == id) {
                tf_values[j]++;
                found = 1;
                break;
            }
        }

        // Novo token
        if (!found) {
            unique_ids[unique_count] = id;
            tf_values[unique_count] = 1;
            unique_count++;
        }
    }

    return unique_count;
}
