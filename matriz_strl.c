#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

MATRIX_STR* criar_matriz(int capacidade) {
    MATRIX_STR* matriz = malloc(sizeof(MATRIX_STR));
    matriz->dados = malloc(capacidade * sizeof(char*)); // cria espaço para os apontadores de char .
    matriz->linhas = 0;
    matriz->capacidade = capacidade;
    return matriz;
}
/////////////r1.2 //////////
void insert_str(MATRIX_STR* matriz, const char* str) {
    if (matriz->linhas >= matriz->capacidade) {
        matriz->capacidade *= 2; // Multiplica o tamanho da capacidade
        matriz->dados = realloc(matriz->dados,matriz->capacidade * sizeof(char*));
        //Pede mais memória para matriz e atualiza o apontador
    }
    // Duplica e insere a string
    matriz->dados[matriz->linhas] = strdup(str); // strdup aloca memória e copia a string
    matriz->linhas++;
}

void lista_da_matriz(MATRIX_STR* matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        printf("%s\n", matriz->dados[i]);
    }
}

void ler_ficheiro_texto(const char* filename, MATRIX_STR* matriz) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        perror("Erro ao abrir ficheiro");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), f)) {
        // remove \n no fim da linha que é obtido pelo fgets e substitui por \0 que é o fim da string
        buffer[strcspn(buffer, "\n")] = '\0';
        insert_str(matriz, buffer);
    }

    fclose(f);
}

void guardar_ficheiro_texto(const char* filename, MATRIX_STR* matriz) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        perror("Erro ao escrever ficheiro");
        return;
    }

    for (int i = 0; i < matriz->linhas; i++) {
        fprintf(f, "%s\n", matriz->dados[i]);
    }

    fclose(f);
}

int procurar_frase(MATRIX_STR* matriz, const char* frase) {
    // for serve para percorrer todas as linhas da matriz e strcmp serve para comparar as strings
    for (int i = 0; i < matriz->linhas; i++) {
        if (strcmp(matriz->dados[i], frase) == 0) {
            return i;
        }
    }
    return -1; // caso nao encontre a frase retorna -1
}

int procurar_substring(MATRIX_STR* matriz, const char* sub) {
    for (int i = 0; i < matriz->linhas; i++) {
        if (strstr(matriz->dados[i], sub)) {
            return i;
        }
    }
    return -1;
}

int remover_frase(MATRIX_STR* matriz, const char* frase) {
    int pos = procurar_frase(matriz, frase);
    if (pos == -1) return 0; // Caso nao encontre a frase retorna 0

    free(matriz->dados[pos]); // Liberta a memória da string que vai ser eliminada

    for (int i = pos; i < matriz->linhas - 1; i++) {
        matriz->dados[i] = matriz->dados[i + 1];
    }

    matriz->linhas--;
    return 1;
}/////////R1.2 FIM //////

void libertar_matriz(MATRIX_STR* matriz) {
    for (int i = 0; i < matriz->linhas; i++) {
        free(matriz->dados[i]);
    }
    free(matriz->dados); // apaga o apontador de apontadores
    free(matriz); // apaga a estrutura
}

MATRIX_INT* create_matrix_int(int capacity) {
    MATRIX_INT* m = malloc(sizeof(MATRIX_INT));
    m->dados_int = malloc(sizeof(int*) * capacity);
    m->linhas_int = 0;
    m->capacidade_int = capacity;
    return m;
}
  // inserir um vetor de inteiros na matriz para os tokens
void insert_int_vector(MATRIX_INT* m, int* vector, int length) {
    if (m->linhas_int >= m->capacidade_int) {
        m->capacidade_int *= 2;
        m->dados_int = realloc(m->dados_int, sizeof(int*) * m->capacidade_int);
    }

    m->dados_int[m->linhas_int] = malloc(sizeof(int) * (length + 1));
    m->dados_int[m->linhas_int][0] = length; // guarda o tamanho na primeira posição

    for (int i = 0; i < length; i++) {
        m->dados_int[m->linhas_int][i + 1] = vector[i];
    }

    m->linhas_int++;
}
// Criar lista para todos os vetores
void list_matrix_int(MATRIX_INT* m) {
    for (int i = 0; i < m->linhas_int; i++) {
        int length = m->dados_int[i][0];
        printf("[%d] -> ", i);
        for (int j = 1; j <= length; j++) {
            printf("%d ", m->dados_int[i][j]);
        }
        printf("\n");
    }
}
// libertar a matriz de inteiros
void free_matrix_int(MATRIX_INT* m) {
    for (int i = 0; i < m->linhas_int; i++) {
        free(m->dados_int[i]);
    }
    free(m->dados_int);
    free(m);
}

int find_token_id(MATRIX_STR* tokens, const char* word) {
    for (int i = 0; i < tokens->linhas; i++) {
        if (strcmp(tokens->dados[i], word) == 0)
            return i;
    }
    return -1;
}
//tokeniza todas as frases do texto
void tokenize_text(MATRIX_STR* texto, MATRIX_STR* tokens, MATRIX_INT* token_ids) {
    for (int i = 0; i < texto->linhas; i++) {
        char* frase = strdup(texto->dados[i]);
        char* token = strtok(frase, " ");

        int ids[100];
        int lenght = 0;

        while (token) {
            int id = find_token_id(tokens, token);
            if (id != -1) ids[lenght++] = id;
            token = strtok(NULL, " ");
        }

        insert_int_vector(token_ids, ids, lenght);
        free(frase);
    }
}
