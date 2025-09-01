#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exp.h"
#include "tabela_simbolos/tabela_simbolos.h"
#include "parser.h" 


FILE *yyin;


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


