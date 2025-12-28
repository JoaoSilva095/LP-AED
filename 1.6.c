#include <stdio.h>
#include "struct.h"

float calcular_similaridade(int idsA[], int tfA[], int tamA, int idsB[], int tfB[], int tamB) {
    float score = 0.0;
    for (int i = 0; i < tamA; i++) {
        for (int j = 0; j < tamB; j++) {
            if (idsA[i] == idsB[j]) {
                score += (float)(tfA[i] * tfB[j]);
            }
        }
    }
    return score;
}