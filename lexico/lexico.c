#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../exp.h"
#include "tabela_transicao.h"
#include "../tabela_simbolos/tabela_simbolos.h"

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
    int estado = estado_inicial();
    char lexema[256];
    int i = 0;
    int c;

    while ((c = fgetc(yyin)) != EOF) {
        coluna++;
        if (c == '\n') { linha++; coluna = 0; }

        int prox = move(estado, c);

        if (prox == -1) { // sem transição válida
            if (eh_final(estado)) {
                // retrocede caractere não consumido
                ungetc(c, yyin);
                coluna--;

                lexema[i] = '\0';
                return criar_token(tipo_final(estado), lexema, linha, coluna - i + 1);
            } else {
                // estado inválido → erro léxico
                char erro[2] = { (char)c, '\0' };
                return criar_token(TOK_ERROR, erro, linha, coluna);
            }
        } else {
            // Transição válida → acumula caractere no lexema
            lexema[i++] = (char)c;
            estado = prox;
        }
    }

    // Fim do arquivo
    if (eh_final(estado)) {
        lexema[i] = '\0';
        return criar_token(tipo_final(estado), lexema, linha, coluna - i + 1);
    }

    return criar_token(TOK_EOF, "EOF", linha, coluna);
}


//implementação da função yylex dirigida por tabela