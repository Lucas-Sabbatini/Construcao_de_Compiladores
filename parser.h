#ifndef PARSER_H
#define PARSER_H

#include "exp.h"

typedef enum {
    NODE_PROGRAMA,
    NODE_BLOCO,
    NODE_DECLARACAO_VARS,
    NODE_LISTA_IDS,
    NODE_LISTA_IDS_LINHA,
    NODE_TIPO,
    NODE_SEQUENCIA_COMANDOS,
    NODE_COMANDO,
    NODE_COMANDO_ATRIBUICAO,
    NODE_COMANDO_SELECAO,
    NODE_PARTE_SENAO,
    NODE_COMANDO_OU_BLOCO,
    NODE_COMANDO_REPETICAO,
    NODE_CONDICAO,
    NODE_OP_RELACIONAL,
    NODE_EXPRESSAO,
    NODE_EXPRESSAO_LINHA,
    NODE_TERMO,
    NODE_TERMO_LINHA,
    NODE_FATOR,
    NODE_CONSTANTE,
    // Nós que representam terminais específicos
    NODE_ID,
    NODE_CONST_INT,
    NODE_CONST_FLOAT,
    NODE_CONST_CHAR,
    NODE_OP_ARITMETICO,
    NODE_ASSIGN,
    NODE_ABRE_PARENT,
    NODE_FECHA_PARENT,
    NODE_PONTO_VIRGULA,
    NODE_VIRGULA,
    NODE_SETA,
    // Nós para palavras reservadas
    NODE_MAIN, NODE_INICIO, NODE_FIM, NODE_INT, NODE_CHAR, NODE_FLOAT,
    NODE_CASO, NODE_ENTAO, NODE_SENAO, NODE_ENQUANTO, NODE_FACA, NODE_REPITA, NODE_ATE,
    NODE_ERROR
} NodeType;

#define MAX_CHILDREN 10 

typedef struct ASTNode {
    NodeType type;
    Token *token; 
    struct ASTNode *children[MAX_CHILDREN];
    int num_children;
    int line;
    int column;
} ASTNode;

ASTNode *create_node(NodeType type, Token *token);
void add_child(ASTNode *parent, ASTNode *child);
void free_ast(ASTNode *node);
void print_ast(ASTNode *node, int indent);

void init_parser(FILE *input_file);
void report_syntax_error(const char *expected);
void match(nome_token expected_type);

ASTNode *parse_Programa();
ASTNode *parse_Bloco();
ASTNode *parse_DeclaracaoVars();
ASTNode *parse_ListaIds();
ASTNode *parse_ListaIdsLinha();
ASTNode *parse_Tipo();
ASTNode *parse_SequenciaComandos();
ASTNode *parse_Comando();
ASTNode *parse_ComandoAtribuicao();
ASTNode *parse_ComandoSelecao();
ASTNode *parse_ParteSenao();
ASTNode *parse_ComandoOuBloco();
ASTNode *parse_ComandoRepeticao();
ASTNode *parse_Condicao();
ASTNode *parse_OpRelacional();
ASTNode *parse_Expressao();
ASTNode *parse_ExpressaoLinha(ASTNode *left_node);
ASTNode *parse_Termo();
ASTNode *parse_TermoLinha(ASTNode *left_node);
ASTNode *parse_Fator();
ASTNode *parse_Constante();

void analisar();

extern FILE *yyin;
Token *yylex(void);
const char* token_nome_string(nome_token nome);
const char* node_type_string(NodeType type); 

#endif // PARSER_H


