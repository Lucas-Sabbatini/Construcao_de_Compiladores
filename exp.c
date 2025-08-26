#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exp.h"
#include "tabela_simbolos.h"

Token* criar_token(nome_token nome, const char* atributo, int linha, int coluna) {
    if (nome == TOK_ERROR) {
        fprintf(stderr, "Erro Léxico na Linha %d, Coluna %d: Caractere(s) inesperado(s) '%s'\n", 
                linha, coluna, atributo);
        exit(EXIT_FAILURE);
    }

    Token* novo_token = (Token*) malloc(sizeof(Token));
    if (novo_token == NULL) {
        fprintf(stderr, "Erro de alocação de memória para o token.\n");
        exit(EXIT_FAILURE);
    }
   
    novo_token->nome = nome;
    novo_token->atributo = strdup(atributo);
    novo_token->linha = linha;
    novo_token->coluna = coluna;
    if (nome == CONST_CHAR || nome == CONST_FLOAT || nome == CONST_INT || nome == TOK_ID ){
        switch (nome)
        {
        case CONST_INT:
            int vali = atoi(atributo);
            install(novo_token->atributo, novo_token->nome, &vali, 1);
            break;
        case CONST_FLOAT:
            float valf = (float) atof(atributo);
            install(novo_token->atributo, novo_token->nome, &valf, 2);
            break;
        case CONST_CHAR:
            char valc = atributo[1];
            install(novo_token->atributo, novo_token->nome, &valc, 3);
            break;
        default:
            install(novo_token->atributo, novo_token->nome, NULL, -1);
            break;
        }
    }

    if (novo_token->atributo == NULL) {
        fprintf(stderr, "Erro de alocação de memória para o atributo.\n");
        free(novo_token);
        exit(EXIT_FAILURE);
    }
    
    return novo_token;
}

const char* token_nome_string(nome_token nome) {
    switch (nome) {
        case TOK_MAIN: return "MAIN";
        case TOK_INICIO: return "INICIO";
        case TOK_FIM: return "FIM";
        case TOK_INT: return "INT";
        case TOK_CHAR: return "CHAR";
        case TOK_FLOAT: return "FLOAT";
        case TOK_CASO: return "CASO";
        case TOK_ENTAO: return "ENTAO";
        case TOK_SENAO: return "SENAO";
        case TOK_ENQUANTO: return "ENQUANTO";
        case TOK_FACA: return "FACA";
        case TOK_REPITA: return "REPITA";
        case TOK_ATE: return "ATE";
        case TOK_ID: return "ID";
        case TOK_RELOP: return "RELOP";
        case TOK_ARTOP: return "ARTOP";
        case CONST_INT: return "CONST_INT";
        case CONST_FLOAT: return "CONST_FLOAT";
        case CONST_CHAR: return "CONST_CHAR";
        case TOK_ASSIGN: return "ASSIGN";
        case TOK_EOF: return "EOF";
        case ABRE_PARENT: return "ABRE_PARENT";
        case FECHA_PARENT: return "FECHA_PARENT";
        case PONTO_VIRGULA: return "PONTO_VIRGULA";
        case VIRGULA: return "VIRGULA";
        case SETA: return "SETA";
        case TOK_ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

void imprime_token(Token* token) {
    if (token == NULL) return;
    printf("| %-15s | %-25s | %5d | %6d |\n", 
           token_nome_string(token->nome), 
           token->atributo, 
           token->linha, 
           token->coluna);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo '%s'\n", argv[1]);
        return 1;
    }

    printf("Iniciando análise léxica do arquivo: %s\n\n", argv[1]);

    Token *token_atual;
    init_symbol_table();

    printf("+-----------------+---------------------------+-------+--------+\n");
    printf("| TOKEN           | ATRIBUTO                  | LINHA | COLUNA |\n");
    printf("+-----------------+---------------------------+-------+--------+\n");

    while (1) {
        token_atual = yylex();
        imprime_token(token_atual);

        if (token_atual == NULL || token_atual->nome == TOK_EOF) {
            if (token_atual != NULL) {
                free(token_atual->atributo);
                free(token_atual);
            }
            break; 
        }

        free(token_atual->atributo);
        free(token_atual);
    }


    display_symbol_table();
    fclose(yyin);
    return 0;
}