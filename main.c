#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"


int main(void) {
    MATRIX_STR* matriz = criar_matriz(2); // cria matriz com capacidade inicial de 2
    insert_str(matriz, "ola");
    insert_str(matriz, "mundo");
    insert_str(matriz, "isto");
    insert_str(matriz, "e");;
    insert_str(matriz, "uma");;
    insert_str(matriz, "matriz");
    lista_da_matriz(matriz);
    libertar_matriz(&matriz); // liberta a memória mas so funciona com endereço Porque nao sei ...
    lista_da_matriz(matriz);
    return 0;
}

