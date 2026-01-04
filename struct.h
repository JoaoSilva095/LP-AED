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

void libertar_matriz(MATRIX_STR* matriz); // esta localizado na matriz_strl.c

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
void carregar_tudo_do_ficheiro(const char* filename, MATRIX_STR* texto, MATRIX_STR* tokens);

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

//R1.6 - Cálculo da Similaridade por Produto Interno
float calcular_similaridade(int idsA[], int tfA[], int tamA, int idsB[], int tfB[], int tamB);

//R2.1 listas ligadas
typedef struct Token_Node {
    int *token_ids;// ids dos tokens
    int *t_valores;// valores TF
    int tam_vetores;// tamanho dos vetores
    struct Token_Node *next;// apontador para o próximo nó
    struct Token_Node *prev;// apontador para o nó anterior
} Token_Node;

typedef struct {
    Token_Node *head;// apontador para o primeiro nó
    Token_Node *tail;// apontador para o último nó
    int total_tokens;// número total de tokens na lista
} Token_List;

Token_List* criar_lista();
void inserir_no_fim(Token_List* lista, int *ids, int *tfs, int tam);
void listar_tokens(Token_List* lista);


Token_Node* obter_no_posicao(Token_List* lista, int pos);
int remover_no_posicao(Token_List* lista, int pos);

////////////R2.2 - Estrutura DOC (Agregadora)/////////////
///Apontadores para as structs principais
typedef struct {
    MATRIX_STR* texto;       // Matriz com as frases originais
    MATRIX_STR* tokens;      // Matriz com o vocabulário (tokens únicos)
    MATRIX_INT* token_ids;   // Matriz com os IDs (tokenização)
    Token_List* tf_list;     // Lista ligada com os valores TF (R2.1)
} DOC;

void listar_tokens(Token_List* lista);
Token_Node* obter_no_posicao(Token_List* lista, int pos);
int remover_no_posicao(Token_List* lista, int pos);

void libertar_lista(Token_List* lista);
// --- FALTA ADICIONAR ISTO PARA O R2.2 (Similaridade de Jaccard) ---
// Jaccard mede a interseção sobre a união de conjuntos
float calcular_jaccard(int idsA[], int tamA, int idsB[], int tamB);
// Funções de gestão do Documento
DOC* criar_documento();
void libertar_documento(DOC* doc);

void guardar_texto_txt();
void guardar_tokens_txt();
void guardar_tf_txt();
void teste_R2_3(DOC *doc);

#endif