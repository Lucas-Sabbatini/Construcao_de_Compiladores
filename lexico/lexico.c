#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../exp.h"
#include "tabela_transicao.h"
#include "../tabela_simbolos/tabela_simbolos.h"

#define LEXEMA_MAX 1024

extern FILE *yyin;
static int linha = 1, coluna = 0;

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

Token* yylex(void) {
    int c;

    for (;;) {
        do {
            c = fgetc(yyin);
            if (c == EOF) {
                return criar_token(TOK_EOF, "EOF", linha, coluna + 1);
            }
            if (c == '\n') { linha++; coluna = 0; }
            else           { coluna++; }
        } while (isspace(c));

        int estado = estado_inicial();
        char lexema[LEXEMA_MAX];
        int i = 0;

        int linha_ini = linha;
        int coluna_ini = coluna;  

            ungetc(c, yyin);
        coluna--;  

        /* 2) Caminha no AFD consumindo chars até não haver transição */
        while ((c = fgetc(yyin)) != EOF) {
            if (c == '\n') { linha++; coluna = 0; }
            else           { coluna++; }

            int prox = move(estado, c);

            if (prox == -1) {
                if (eh_final(estado)) {
                    /* Se o lookahead NÃO é whitespace, devolve-o para a próxima análise */
                    if (!isspace(c)) {
                        ungetc(c, yyin);
                        coluna--;  
                    }
                    lexema[i] = '\0';

                    nome_token token_reconhecido= tipo_final(estado);

                    if (token_reconhecido == TOK_COMMENT) {
                        // Se o token for um comentário, não o retorne.
                        // Em vez disso, quebre o laço interno para que o laço
                        // principal (for) reinicie a busca pelo próximo token.
                        break; 
                    }

                    int is_palavra_reservada = (token_reconhecido >= TOK_MAIN && token_reconhecido <= TOK_ATE);
                    
                    if (token_reconhecido == TOK_ID || 
                        is_palavra_reservada || 
                        token_reconhecido == CONST_INT || 
                        token_reconhecido == CONST_FLOAT)
                    {
                        if (i > 0) {
                            ungetc(lexema[i-1], yyin);
                            lexema[i-1] = '\0';
                        }
                    }

                    if (token_reconhecido != TOK_ASSIGN)

                    return criar_token(token_reconhecido, lexema, linha_ini, coluna_ini);
                } else {
                    if (isspace(c)) {
                        break; 
                    }
                    char erro[2] = { (char)c, '\0' };
                    return criar_token(TOK_ERROR, erro, linha, coluna);
                }
            } else {
                if (i < LEXEMA_MAX - 1) {
                    lexema[i++] = (char)c;
                } else {
                    return criar_token(TOK_ERROR, "lexema muito longo", linha_ini, coluna_ini);
                }
                estado = prox;
            }
        }

        if (feof(yyin)) {
            if (i > 0 && eh_final(estado)) {
                lexema[i] = '\0';
                return criar_token(tipo_final(estado), lexema, linha_ini, coluna_ini);
            }
            return criar_token(TOK_EOF, "EOF", linha, coluna + 1);
        }

    }
}