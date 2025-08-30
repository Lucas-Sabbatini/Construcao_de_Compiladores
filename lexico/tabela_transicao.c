#include <ctype.h>
#include "tabela_transicao.h"
#include "../exp.h"

// Definições
#define ESTADOS 8
#define ALFABETO 128  // ASCII

// Estados finais
// -1 = não-final, caso contrário indica o tipo de token
static int finais[ESTADOS] = {
    -1,        // 0: inicial
    TOK_ID,    // 1: identificador
    CONST_INT, // 2: inteiro
    TOK_RELOP, // 3: < ou >
    TOK_RELOP, // 4: <= ou >=
    TOK_RELOP, // 5: =
    TOK_RELOP, // 6: ==
    TOK_RELOP  // 7: !=
};

// Tabela de transição
// move[estado][caractere] = próximo estado
static int transicoes[ESTADOS][ALFABETO];

// Inicializa a tabela (simples)
static void init_tabela(void) {
    static int inicializado = 0;
    if (inicializado) return;
    inicializado = 1;

    // Inicializa tudo com -1 (sem transição)
    for (int s = 0; s < ESTADOS; s++)
        for (int c = 0; c < ALFABETO; c++)
            transicoes[s][c] = -1;

    // Identificadores: letra -> estado 1, depois letras/dígitos continuam em 1
    for (char c = 'a'; c <= 'z'; c++) transicoes[0][(int)c] = 1;
    for (char c = 'A'; c <= 'Z'; c++) transicoes[0][(int)c] = 1;
    for (char c = 'a'; c <= 'z'; c++) transicoes[1][(int)c] = 1;
    for (char c = 'A'; c <= 'Z'; c++) transicoes[1][(int)c] = 1;
    for (char c = '0'; c <= '9'; c++) transicoes[1][(int)c] = 1;

    // Números inteiros
    for (char c = '0'; c <= '9'; c++) {
        transicoes[0][(int)c] = 2;
        transicoes[2][(int)c] = 2;
    }

    // Operadores relacionais
    transicoes[0]['<'] = 3;  
    transicoes[0]['>'] = 3;  
    transicoes[0]['='] = 5;  
    transicoes[3]['='] = 4;  // <= ou >=
    transicoes[5]['='] = 6;  // ==
    transicoes[0]['!'] = 7;
    transicoes[7]['='] = 7;  // !=
}

// Funções da interface -----------------

int estado_inicial(void) {
    init_tabela();
    return 0;
}

int eh_final(int estado) {
    return finais[estado] != -1;
}

nome_token tipo_final(int estado) {
    if (estado < 0 || estado >= ESTADOS) return TOK_ERROR;
    return finais[estado] == -1 ? TOK_ERROR : finais[estado];
}

int move(int estado, int c) {
    if (estado < 0 || estado >= ESTADOS) return -1;
    if (c < 0 || c >= ALFABETO) return -1;
    return transicoes[estado][c];
}
