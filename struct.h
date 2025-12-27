#ifndef PROJETO_STRUCT_H
#define PROJETO_STRUCT_H

//R1.1 e R1.2 - Estruturas de Matrizes
typedef struct {
    char **dados;
    int linhas;
    int capacidade;
} MATRIX_STR;
// Funcoes para matriz de strings
MATRIX_STR* criar_matriz(int capacidade);
////// R1.2 //////////
// Insere uma string na matriz, redimensionando se necessario.
void insert_str(MATRIX_STR* matriz, const char* str);
void lista_da_matriz(MATRIX_STR* matriz);
void ler_ficheiro_texto(const char* filename, MATRIX_STR* matriz);
void guardar_ficheiro_texto(const char* filename, MATRIX_STR* matriz);
int procurar_frase(MATRIX_STR* matriz, const char* frase);
int procurar_substring(MATRIX_STR* matriz, const char* sub);
int remover_frase(MATRIX_STR* matriz, const char* frase);
///////R1.2 FIM //////

void libertar_matriz(MATRIX_STR* matriz);

/* -------- MATRIZ DE INTEIROS -------- */
typedef struct {
    int **dados_int;
    int linhas_int;
    int capacidade_int;
} MATRIX_INT;

MATRIX_INT* create_matrix_int(int capacidade_int);
void insert_int_vector(MATRIX_INT* m, int* vector, int length);
void list_matrix_int(MATRIX_INT* m);
void free_matrix_int(MATRIX_INT* m);

int find_token_id(MATRIX_STR* tokens, const char* word);
//// Tokeniza todas as frases do texto
void tokenize_text(MATRIX_STR* texto, MATRIX_STR* tokens, MATRIX_INT* token_ids);

//R1.3 - Estrutura para pares de tokens
typedef struct {
    char token1[100];
    char token2[100];
    int freq;
} ParFreq;

//Funções R1.3 - Cálculo do Alfabeto
int encontrar_par(ParFreq *lista, int total, char *t1, char *t2);
void executar_R1_3(char ***frase, int *num_tokens_frase, char ***alfabeto, int *num_tokens_alfabeto, int objetivo);

//R1.4 - Estrutura para vocabulário
typedef struct {
    char *token;
    int id;
} Token;


//Funções R1.4 - Tokenização Greedy
#define SD_ID -1
#define MAX_OUTPUT 1000
int tokenize_greedy(const char *text, Token vocab[], int vocab_size, int output_ids[], int max_output);

//Funções R1.5 - Cálculo TF
#define MAX_TF 1000
int compute_tf(int token_ids[], int token_count, int unique_ids[], int tf_values[]);

#endif