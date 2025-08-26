#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabela_simbolos.h"


#define TABLE_SIZE 100

static Symbol *symbol_table[TABLE_SIZE];

static unsigned int hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash % TABLE_SIZE;
}


void init_symbol_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        symbol_table[i] = NULL;
    }
}

Symbol *lookup(char *lexeme) {
    unsigned int index = hash(lexeme);
    Symbol *s = symbol_table[index];
    while (s != NULL && strcmp(s->lexeme, lexeme) != 0) {
        s = s->next;
    }
    return s;
}

void install(char *lexeme, nome_token token_name, void *val, int data_type) {
    if (lookup(lexeme) == NULL) {
        unsigned int index = hash(lexeme);
        Symbol *new_symbol = (Symbol*) malloc(sizeof(Symbol));
        if (new_symbol == NULL) {
            fprintf(stderr, "Erro de alocação de memória para o símbolo.\n");
            exit(EXIT_FAILURE);
        }
        new_symbol->lexeme = strdup(lexeme);
        new_symbol->token_name = token_name;
        new_symbol->data_type = -1;
        new_symbol->next = symbol_table[index];

        switch (data_type)
        {
        case 1:
            new_symbol->data_type = 1;
            new_symbol->value.int_val = *((int*) val);
            break;
         case 2:
            new_symbol->data_type = 2;
            new_symbol->value.float_val = *((float*) val);
            break;
         case 3:
            new_symbol->data_type = 3;
            new_symbol->value.char_val = *((char*) val);
            break;
         default:
            break;
        }

        symbol_table[index] = new_symbol;
    }
}

void display_symbol_table() {
    printf("\n--- Tabela de Símbolos ---\n");
    printf("%-15s | %-15s | %-10s | %s\n", "Lexema", "Token", "Tipo", "Valor");
    printf("-----------------|-----------------|------------|----------------\n");

    for (int i = 0; i < TABLE_SIZE; i++) {
        Symbol *s = symbol_table[i];
        while (s != NULL) {
            printf("%-15s | %-15s | ", s->lexeme, token_nome_string(s->token_name));

            switch (s->data_type) {
                case 1:
                    printf("%-10s | %d\n", "int", s->value.int_val);
                    break;
                case 2:
                    printf("%-10s | %.2f\n", "float", s->value.float_val);
                    break;
                case 3:
                    printf("%-10s | %c\n", "char", s->value.char_val);
                    break;
                default:
                    printf("%-10s | %s\n", "-", "-");
                    break;
            }

            s = s->next;
        }
    }
}