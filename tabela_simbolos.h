#ifndef TABELA_SIMBOLOS_H
#define TABELA_SIMBOLOS_H

#include "exp.h" 

typedef struct Symbol {
    char *lexeme;
    nome_token token_name;
    int data_type; 
    union {
        int int_val;
        float float_val;
        char char_val;
    } value;
    struct Symbol *next; 
} Symbol;


void init_symbol_table();

void install(char *lexeme, nome_token token_name, void *val, int data_type);

Symbol *lookup(char *lexeme);

void display_symbol_table();

#endif