#ifndef EXP_H
#define EXP_H

typedef enum {
    // Palavras reservadas
    TOK_MAIN, TOK_INICIO, TOK_FIM, TOK_INT, TOK_CHAR, TOK_FLOAT,
    TOK_CASO, TOK_ENTAO, TOK_SENAO, TOK_ENQUANTO, TOK_FACA, TOK_REPITA, TOK_ATE,

    // Tipos de token com atributo
    TOK_ID,         // Identificador
    TOK_RELOP,      // Operador Relacional (>, <, >=, <=, ==, !=)
    TOK_ARTOP,       // Operador Aritimético
    CONST_INT,    // Número Inteiro
    CONST_FLOAT,  // Número Float
    CONST_CHAR,     // Caractere

    // Tokens simples
    TOK_ASSIGN,     // Atribuição (=)
    TOK_EOF,        // Fim de arquivo
    ABRE_PARENT,    // (
    FECHA_PARENT,   // )
    PONTO_VIRGULA,  // ;
    VIRGULA,        // ,
    SETA,           // ->


    // Tokens para ignorar ou tratar erros
    TOK_SEPARATOR,  // Separadores como espaço, tab, newline
    TOK_COMMENT,    // Comentários de bloco
    TOK_ERROR       // Token não reconhecido
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