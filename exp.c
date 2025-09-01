#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exp.h"
#include "tabela_simbolos.h"
#include "parser.h" 

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

// A função token_nome_string foi movida para exp.h

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo '%s'\n", argv[1]);
        return 1;
    }

    printf("Iniciando análise sintática do arquivo: %s\n\n", argv[1]);

    init_symbol_table(); // Inicializa a tabela de símbolos
    init_parser(input_file); // Inicializa o analisador sintático com o arquivo de entrada

    ASTNode *root = parse_Programa(); // Inicia a análise sintática

    if (root != NULL) {
        printf("Análise Sintática concluída com sucesso! Árvore de derivação:\n");
        print_ast(root, 0); // Imprime a árvore para verificação
        free_ast(root); // Libera a memória da AST
    } else {
        printf("Análise Sintática falhou.\n");
    }

    // display_symbol_table(); // Opcional: exibir tabela de símbolos após a análise
    fclose(input_file);
    return 0;
}


