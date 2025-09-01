#ifndef EXP_H
#define EXP_H

#include <stdio.h>

typedef enum {
    TOK_MAIN, TOK_INICIO, TOK_FIM, TOK_INT, TOK_CHAR, TOK_FLOAT,
    TOK_CASO, TOK_ENTAO, TOK_SENAO, TOK_ENQUANTO, TOK_FACA, TOK_REPITA, TOK_ATE,

    TOK_ID,         
    TOK_RELOP,     
    TOK_ARTOP,       
    CONST_INT,    
    CONST_FLOAT,  
    CONST_CHAR,     
    
    TOK_ASSIGN,     
    TOK_EOF,        
    ABRE_PARENT,    
    FECHA_PARENT,   
    PONTO_VIRGULA,  
    VIRGULA,        
    SETA,           


    TOK_SEPARATOR, 
    TOK_COMMENT,    
    TOK_ERROR       
} nome_token;

typedef struct {
    nome_token nome;
    char *atributo; 
    int linha;
    int coluna;
} Token;

extern FILE *yyin; 
Token *yylex(void); 
const char* token_nome_string(nome_token nome); 
Token* criar_token(nome_token nome, const char* atributo, int linha, int coluna); 

#endif //EXP_H


