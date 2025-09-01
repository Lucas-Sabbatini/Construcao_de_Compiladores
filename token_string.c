#include <stdio.h>
#include "sintatico/parser.h"

// Função para retornar o nome do token como string (para depuração e mensagens de erro)
const char* token_nome_string(nome_token nome) {
    switch (nome) {
        case TOK_MAIN: return "TOK_MAIN";
        case TOK_INICIO: return "TOK_INICIO";
        case TOK_FIM: return "TOK_FIM";
        case TOK_INT: return "TOK_INT";
        case TOK_CHAR: return "TOK_CHAR";
        case TOK_FLOAT: return "TOK_FLOAT";
        case TOK_CASO: return "TOK_CASO";
        case TOK_ENTAO: return "TOK_ENTAO";
        case TOK_SENAO: return "TOK_SENAO";
        case TOK_ENQUANTO: return "TOK_ENQUANTO";
        case TOK_FACA: return "TOK_FACA";
        case TOK_REPITA: return "TOK_REPITA";
        case TOK_ATE: return "TOK_ATE";
        case TOK_ID: return "TOK_ID";
        case TOK_RELOP: return "TOK_RELOP";
        case TOK_ARTOP: return "TOK_ARTOP";
        case CONST_INT: return "CONST_INT";
        case CONST_FLOAT: return "CONST_FLOAT";
        case CONST_CHAR: return "CONST_CHAR";
        case TOK_ASSIGN: return "TOK_ASSIGN";
        case TOK_EOF: return "TOK_EOF";
        case ABRE_PARENT: return "ABRE_PARENT";
        case FECHA_PARENT: return "FECHA_PARENT";
        case PONTO_VIRGULA: return "PONTO_VIRGULA";
        case VIRGULA: return "VIRGULA";
        case SETA: return "SETA";
        case TOK_SEPARATOR: return "TOK_SEPARATOR";
        case TOK_COMMENT: return "TOK_COMMENT";
        case TOK_ERROR: return "TOK_ERROR";
        default: return "UNKNOWN_TOKEN";
    }
}

// Função separada para retornar o nome do tipo de nó da AST como string
const char* node_type_string(NodeType type) {
    switch (type) {
        case NODE_PROGRAMA: return "NODE_PROGRAMA";
        case NODE_BLOCO: return "NODE_BLOCO";
        case NODE_DECLARACAO_VARS: return "NODE_DECLARACAO_VARS";
        case NODE_LISTA_IDS: return "NODE_LISTA_IDS";
        case NODE_LISTA_IDS_LINHA: return "NODE_LISTA_IDS_LINHA";
        case NODE_TIPO: return "NODE_TIPO";
        case NODE_SEQUENCIA_COMANDOS: return "NODE_SEQUENCIA_COMANDOS";
        case NODE_COMANDO: return "NODE_COMANDO";
        case NODE_COMANDO_ATRIBUICAO: return "NODE_COMANDO_ATRIBUICAO";
        case NODE_COMANDO_SELECAO: return "NODE_COMANDO_SELECAO";
        case NODE_PARTE_SENAO: return "NODE_PARTE_SENAO";
        case NODE_COMANDO_OU_BLOCO: return "NODE_COMANDO_OU_BLOCO";
        case NODE_COMANDO_REPETICAO: return "NODE_COMANDO_REPETICAO";
        case NODE_CONDICAO: return "NODE_CONDICAO";
        case NODE_OP_RELACIONAL: return "NODE_OP_RELACIONAL";
        case NODE_EXPRESSAO: return "NODE_EXPRESSAO";
        case NODE_EXPRESSAO_LINHA: return "NODE_EXPRESSAO_LINHA";
        case NODE_TERMO: return "NODE_TERMO";
        case NODE_TERMO_LINHA: return "NODE_TERMO_LINHA";
        case NODE_FATOR: return "NODE_FATOR";
        case NODE_CONSTANTE: return "NODE_CONSTANTE";
        case NODE_ID: return "NODE_ID";
        case NODE_CONST_INT: return "NODE_CONST_INT";
        case NODE_CONST_FLOAT: return "NODE_CONST_FLOAT";
        case NODE_CONST_CHAR: return "NODE_CONST_CHAR";
        case NODE_OP_ARITMETICO: return "NODE_OP_ARITMETICO";
        case NODE_ASSIGN: return "NODE_ASSIGN";
        case NODE_ABRE_PARENT: return "NODE_ABRE_PARENT";
        case NODE_FECHA_PARENT: return "NODE_FECHA_PARENT";
        case NODE_PONTO_VIRGULA: return "NODE_PONTO_VIRGULA";
        case NODE_VIRGULA: return "NODE_VIRGULA";
        case NODE_SETA: return "NODE_SETA";
        case NODE_MAIN: return "NODE_MAIN";
        case NODE_INICIO: return "NODE_INICIO";
        case NODE_FIM: return "NODE_FIM";
        case NODE_INT: return "NODE_INT";
        case NODE_CHAR: return "NODE_CHAR";
        case NODE_FLOAT: return "NODE_FLOAT";
        case NODE_CASO: return "NODE_CASO";
        case NODE_ENTAO: return "NODE_ENTAO";
        case NODE_SENAO: return "NODE_SENAO";
        case NODE_ENQUANTO: return "NODE_ENQUANTO";
        case NODE_FACA: return "NODE_FACA";
        case NODE_REPITA: return "NODE_REPITA";
        case NODE_ATE: return "NODE_ATE";
        case NODE_ERROR: return "NODE_ERROR";
        default: return "UNKNOWN_NODE_TYPE";
    }
}


