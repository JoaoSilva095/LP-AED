#ifndef PROJETO_STRUCTS_H
#define PROJETO_STRUCTS_H

// Estrutura para contar pares de tokens (R1.3)
typedef struct {
    char token1[100];
    char token2[100];
    int freq;
} ParFreq;

// Estrutura para o vocabulário (R1.4 e R1.5)
typedef struct {
    char *token;
    int id;
} Token;

int encontrar_par(
    ParFreq *lista,
    int total,
    char *t1,
    char *t2);


void executar_R1_3(
    char ***frase,
    int *num_tokens_frase,
    char ***alfabeto,
    int *num_tokens_alfabeto,
    int objetivo);

#endif