#include <ctype.h>
#include "tabela_transicao.h"
#include "../exp.h"

#define ESTADOS 111
#define ALFABETO 128  

static nome_token finais[ESTADOS] = {
    // Inicializa todos os estados como não-finais (-1)
    [0 ... ESTADOS-1] = -1,

    // Popula os estados finais de acordo com a tabela AFD
    [3] = TOK_ID,
    [6] = CONST_INT,
    [8] = CONST_FLOAT,
    [12] = CONST_FLOAT,
    [14] = TOK_SEPARATOR,
    [18] = TOK_COMMENT,
    [19] = TOK_ASSIGN,
    [21] = SETA,
    [22] = ABRE_PARENT,
    [23] = FECHA_PARENT,
    [24] = PONTO_VIRGULA,
    [25] = VIRGULA,
    [30] = TOK_MAIN,
    [37] = TOK_INICIO,
    [41] = TOK_FIM,
    [45] = TOK_INT,
    [50] = TOK_CHAR,
    [56] = TOK_FLOAT,
    [61] = TOK_CASO,
    [67] = TOK_ENTAO,
    [73] = TOK_SENAO,
    [82] = TOK_ENQUANTO,
    [87] = TOK_FACA,
    [94] = TOK_REPITA,
    [98] = TOK_ATE,
    [100] = TOK_RELOP,
    [101] = TOK_RELOP,
    [103] = TOK_RELOP,
    [105] = TOK_RELOP,
    [106] = TOK_ARTOP,
    [109] = CONST_CHAR,
    [110] = TOK_EOF,
};

static int transicoes[ESTADOS][ALFABETO];

static void init_tabela(void) {
    static int inicializado = 0;
    if (inicializado) return;
    inicializado = 1;

    for (int s = 0; s < ESTADOS; s++) {
        for (int c = 0; c < ALFABETO; c++) {
            transicoes[s][c] = -1;
        }
    }
    int estadosNFinais[] = {27, 28, 29, 31, 32, 33, 34, 35, 36, 38, 39, 40, 42, 43, 44, 46, 47, 48, 49, 51, 52, 53, 54, 55, 57, 58, 59, 60, 62, 64, 65, 66, 68, 69, 70, 71, 72, 74, 77, 78, 79, 80, 81, 83, 84, 85, 86, 88, 89, 90, 91, 92, 93, 95, 96, 97};
    for(int i=0;i<56;i++){
        for (int c = 0; c < ALFABETO; c++) {
            if (isalnum(c) || c == '_') {
                transicoes[estadosNFinais[i]][c] = 2;
            }
        }
    }
    



    // Estado 0
    for (char c = 'a'; c <= 'z'; c++) { transicoes[0][(int)c] = 1; }
    for (char c = 'A'; c <= 'Z'; c++) { transicoes[0][(int)c] = 1; }
    transicoes[0]['_'] = 1;
    for (char c = '0'; c <= '9'; c++) { transicoes[0][(int)c] = 4; }
    transicoes[0][' '] = 13; transicoes[0]['\t'] = 13; transicoes[0]['\n'] = 13;
    transicoes[0]['+'] = 106; transicoes[0]['-'] = 106;
    transicoes[0]['/'] = 15; transicoes[0]['*'] = 106;
    transicoes[0]['='] = 102; transicoes[0]['-'] = 20;
    transicoes[0]['>'] = 100; transicoes[0]['('] = 22;
    transicoes[0][')'] = 23; transicoes[0][';'] = 24;
    transicoes[0][','] = 25; transicoes[0]['<'] = 100;
    transicoes[0]['!'] = 104; transicoes[0]['^'] = 106;
    transicoes[0]['\''] = 107; transicoes[0]['m'] = 26;
    transicoes[0]['a'] = 95; transicoes[0]['i'] = 31;
    transicoes[0]['n'] = 1; transicoes[0]['c'] = 46;
    transicoes[0]['o'] = 1; transicoes[0]['f'] = 38;
    transicoes[0]['h'] = 1; transicoes[0]['r'] = 88;
    transicoes[0]['l'] = 1; transicoes[0]['t'] = 1;
    transicoes[0]['s'] = 68; transicoes[0]['e'] = 62;
    transicoes[0]['q'] = 1; transicoes[0]['u'] = 1;
    transicoes[0]['p'] = 1;

    // Estado 1
    for (char c = 'a'; c <= 'z'; c++) { transicoes[1][(int)c] = 2; }
    for (char c = 'A'; c <= 'Z'; c++) { transicoes[1][(int)c] = 2; }
    for (char c = '0'; c <= '9'; c++) { transicoes[1][(int)c] = 2; }
    transicoes[1]['_'] = 2;

    // Estado 2
    for (char c = 'a'; c <= 'z'; c++) { transicoes[2][(int)c] = 2; }
    for (char c = 'A'; c <= 'Z'; c++) { transicoes[2][(int)c] = 2; }
    for (char c = '0'; c <= '9'; c++) { transicoes[2][(int)c] = 2; }
    transicoes[2]['_'] = 2;
    transicoes[2][' '] = 3; transicoes[2]['\t'] = 3; transicoes[2]['\n'] = 3;
    transicoes[2]['+'] = 3; transicoes[2]['-'] = 3;
    transicoes[2]['/'] = 3; transicoes[2]['*'] = 3;
    transicoes[2]['='] = 3; transicoes[2]['>'] = 3;
    transicoes[2]['('] = 3; transicoes[2][')'] = 3;
    transicoes[2][';'] = 3; transicoes[2][','] = 3;
    transicoes[2]['<'] = 3; transicoes[2]['!'] = 3;
    transicoes[2]['^'] = 3; transicoes[2]['"'] = 3;
    transicoes[2]['.'] = 3;

    // Estado 4
    for (char c = 'a'; c <= 'z'; c++) { transicoes[4][(int)c] = 6; }
    for (char c = 'A'; c <= 'Z'; c++) { transicoes[4][(int)c] = 6; }
    transicoes[4]['_'] = 6;
    for (char c = '0'; c <= '9'; c++) { transicoes[4][(int)c] = 4; }
    transicoes[4][' '] = 6; transicoes[4]['\t'] = 6; transicoes[4]['\n'] = 6;
    transicoes[4]['+'] = 6; transicoes[4]['-'] = 6;
    transicoes[4]['/'] = 6; transicoes[4]['*'] = 6;
    transicoes[4]['='] = 6; transicoes[4]['-'] = 6;
    transicoes[4]['>'] = 6; transicoes[4]['('] = 6;
    transicoes[4][')'] = 6; transicoes[4][';'] = 6;
    transicoes[4][','] = 6; transicoes[4]['<'] = 6;
    transicoes[4]['!'] = 6; transicoes[4]['^'] = 6;
    transicoes[4]['"'] = 6; transicoes[4]['.'] = 7;
    transicoes[4]['E'] = 9;

    // Estado 5
    for (char c = '0'; c <= '9'; c++) { transicoes[5][(int)c] = 8; }
    transicoes[5]['+'] = 10; transicoes[5]['-'] = 10;

    // Estado 7
    for (char c = 'a'; c <= 'z'; c++) { transicoes[7][(int)c] = 8; }
    for (char c = 'A'; c <= 'Z'; c++) { transicoes[7][(int)c] = 8; }
    transicoes[7]['_'] = 8;
    for (char c = '0'; c <= '9'; c++) { transicoes[7][(int)c] = 7; }
    transicoes[7][' '] = 8; transicoes[7]['\t'] = 8; transicoes[7]['\n'] = 8;
    transicoes[7]['+'] = 8; transicoes[7]['-'] = 8;
    transicoes[7]['/'] = 8; transicoes[7]['*'] = 8;
    transicoes[7]['='] = 8; transicoes[7]['-'] = 8;
    transicoes[7]['>'] = 8; transicoes[7]['('] = 8;
    transicoes[7][')'] = 8; transicoes[7][';'] = 8;
    transicoes[7][','] = 8; transicoes[7]['<'] = 8;
    transicoes[7]['!'] = 8; transicoes[7]['^'] = 8;
    transicoes[7]['"'] = 8; transicoes[7]['E'] = 9;

    // Estado 9
    transicoes[9]['+'] = 10; transicoes[9]['-'] = 10;

    // Estado 10
    for (char c = '0'; c <= '9'; c++) { transicoes[10][(int)c] = 11; }

    // Estado 11
    for (char c = 'a'; c <= 'z'; c++) { transicoes[11][(int)c] = 12; }
    for (char c = 'A'; c <= 'Z'; c++) { transicoes[11][(int)c] = 12; }
    transicoes[11]['_'] = 12;
    for (char c = '0'; c <= '9'; c++) { transicoes[11][(int)c] = 11; }
    for (int c = 0; c < ALFABETO; c++) {
        if (!isalnum(c) && c != '_') {
            transicoes[11][c] = 12;
        }
    }

    // Estado 13
    for (char c = 'a'; c <= 'z'; c++) { transicoes[13][(int)c] = 14; }
    for (char c = 'A'; c <= 'Z'; c++) { transicoes[13][(int)c] = 14; }
    for (char c = '0'; c <= '9'; c++) { transicoes[13][(int)c] = 14; }
    transicoes[13]['_'] = 14;
    transicoes[13][' '] = 13; transicoes[13]['\t'] = 13; transicoes[13]['\n'] = 13;
    transicoes[13]['+'] = 14; transicoes[13]['-'] = 14;
    transicoes[13]['/'] = 14; transicoes[13]['*'] = 14;
    transicoes[13]['='] = 14; transicoes[13]['>'] = 14;
    transicoes[13]['('] = 14; transicoes[13][')'] = 14;
    transicoes[13][';'] = 14; transicoes[13][','] = 14;
    transicoes[13]['<'] = 14; transicoes[13]['!'] = 14;
    transicoes[13]['^'] = 14; transicoes[13]['"'] = 14;
    transicoes[13]['.'] = 14;

    // Estado 15
    transicoes[15]['*'] = 16;

    // Estado 16
    for (char c = 'a'; c <= 'z'; c++) { transicoes[16][(int)c] = 16; }
    for (char c = 'A'; c <= 'Z'; c++) { transicoes[16][(int)c] = 16; }
    for (char c = '0'; c <= '9'; c++) { transicoes[16][(int)c] = 16; }
    transicoes[16]['_'] = 16; transicoes[16][' '] = 16;
    transicoes[16]['\t'] = 16; transicoes[16]['+'] = 16;
    transicoes[16]['-'] = 16; transicoes[16]['/'] = 16;
    transicoes[16]['*'] = 17; transicoes[16]['='] = 16;
    transicoes[16]['>'] = 16; transicoes[16]['('] = 16;
    transicoes[16][')'] = 16; transicoes[16][';'] = 16;
    transicoes[16][','] = 16; transicoes[16]['<'] = 16;
    transicoes[16]['!'] = 16; transicoes[16]['^'] = 16;
    transicoes[16]['"'] = 16; transicoes[16]['.'] = 16;
    transicoes[16]['\n'] = 16;transicoes[16]['\''] = 16;

    transicoes[17]['/'] = 18; 
    

    // Estado 20
    transicoes[20]['-'] = 19; transicoes[20]['>'] = 21;

    // Estado 26
    for (char c = '0'; c <= '9'; c++) { transicoes[26][(int)c] = 2; }
    transicoes[26]['_'] = 2; transicoes[26]['a'] = 27;

    // Estado 27
    transicoes[27]['i'] = 28;

    // Estado 28
    transicoes[28]['n'] = 29;

    // Estado 29
    for (int c = 0; c < ALFABETO; c++) {
                if (!isalnum(c) && c != '_') {
                    transicoes[29][c] = 30;
                }
            }    // Estado 31
    transicoes[31]['n'] = 32;

    // Estado 32
    transicoes[32]['i'] = 33;
    transicoes[32]['t'] = 44;

    // Estado 33
    transicoes[33]['c'] = 34;

    // Estado 34
    transicoes[34]['i'] = 35;

    // Estado 35
    transicoes[35]['o'] = 36;

    // Estado 36
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[36][c] = 37;
            }
        }

    // Estado 38
    transicoes[38]['i'] = 39;
    transicoes[38]['l'] = 52;
    transicoes[38]['a'] = 84;

    // Estado 39
    transicoes[39]['m'] = 40;

    // Estado 40
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[40][c] = 41;
            }
        }

    // Estado 42
    transicoes[42]['n'] = 43;

    // Estado 44
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[44][';'] = 45;
            }
        }

    // Estado 46
    transicoes[46]['h'] = 47;
    transicoes[46]['a'] = 58;

    // Estado 47
    transicoes[47]['a'] = 48;

    // Estado 48
    transicoes[48]['r'] = 49;

    // Estado 49
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[49][c] = 50;
            }
        }

    // Estado 52
    transicoes[52]['o'] = 53;

    // Estado 53
    transicoes[53]['a'] = 54;

    // Estado 54
    transicoes[54]['t'] = 55;

    // Estado 55
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[55][c] = 56;
            }
        }

    // Estado 58
    transicoes[58]['s'] = 59;

    // Estado 59
    transicoes[59]['o'] = 60;

    // Estado 60
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[60][c] = 61;
            }
        }

    // Estado 62
    transicoes[62]['n'] = 63;

    // Estado 63
    transicoes[63]['t'] = 64;
    transicoes[63]['q'] = 76;

    // Estado 64
    transicoes[64]['a'] = 65;

    // Estado 65
    transicoes[65]['o'] = 66;

    //Estado 66
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[66][c] = 67;
            }
        }

    // Estado 68
    transicoes[68]['e'] = 69;

    // Estado 69
    transicoes[69]['n'] = 70;

    // Estado 70
    transicoes[70]['a'] = 71;

    // Estado 71
    transicoes[71]['o'] = 72;

    // Estado 72
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[72][c] = 73;
            }
        }

    // Estado 74
    transicoes[74]['n'] = 75;

    // Estado 75
    transicoes[75]['q'] = 76;

    // Estado 76
    transicoes[76]['u'] = 77;

    // Estado 77
    transicoes[77]['a'] = 78;

    // Estado 78
    transicoes[78]['n'] = 79;

    // Estado 79
    transicoes[79]['t'] = 80;

    // Estado 80
    transicoes[80]['o'] = 81;

    // Estado 81
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[81][c] = 82;
            }
        }

    // Estado 83
    transicoes[83]['a'] = 84;

    // Estado 84
    transicoes[84]['c'] = 85;

    // Estado 85
    transicoes[85]['a'] = 86;
    
    // Estado 86
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[86][c] = 87;
            }
        }

    // Estado 88
    transicoes[88]['e'] = 89;

    // Estado 89
    transicoes[89]['p'] = 90;

    // Estado 90
    transicoes[90]['i'] = 91;

    // Estado 91
    transicoes[91]['t'] = 92;

    // Estado 92
    transicoes[92]['a'] = 93;

    // Estado 94
    for (int c = 0; c < ALFABETO; c++) {
            if (!isalnum(c) && c != '_') {
                transicoes[93][c] = 94;
            }
        }

    // Estado 95
    transicoes[95]['t'] = 96;

    // Estado 96
    transicoes[96]['e'] = 97;

    // Estado 97
    for (int c = 0; c < ALFABETO; c++) {
        if (!isalnum(c) && c != '_') {
            transicoes[97][c] = 98;
        }
    }

    // Estado 100
    transicoes[100]['='] = 101;

    // Estado 102
    transicoes[102]['='] = 103;
    for (int c = 0; c < ALFABETO; c++) {
        if (c != '=') {
            transicoes[102][c] = 19;
        }
    }

    // Estado 104
    transicoes[104]['='] = 105;

    // Estado 107
    transicoes[107]['\''] = 109;
    for(int c=0; c < ALFABETO; c++) { if(c != '"') transicoes[107][c] = 108; }


    // Estado 108
    transicoes[108]['\''] = 109;
}

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
