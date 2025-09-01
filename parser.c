#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// --- NOVO: Buffer de Lookahead ---
#define LOOKAHEAD_BUFFER_SIZE 20
Token *lookahead_buffer[LOOKAHEAD_BUFFER_SIZE];
int current_token_index = 0;

// --- Protótipos de funções locais ---
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

// --- Implementação do Buffer ---
void fill_buffer() {
    for (int i = 0; i < LOOKAHEAD_BUFFER_SIZE; i++) {
        lookahead_buffer[i] = yylex();
    }
}

Token* peek_token(int k) {
    if (k < 0 || k >= LOOKAHEAD_BUFFER_SIZE) {
        fprintf(stderr, "Erro: Tentativa de olhar muito à frente no buffer.\n");
        exit(EXIT_FAILURE);
    }
    return lookahead_buffer[(current_token_index + k) % LOOKAHEAD_BUFFER_SIZE];
}

void consume_token() {
    lookahead_buffer[current_token_index] = yylex();
    current_token_index = (current_token_index + 1) % LOOKAHEAD_BUFFER_SIZE;
}

#define lookahead_token (peek_token(0))

// --- Funções Auxiliares da AST ---
ASTNode *create_node(NodeType type, Token *token) {
    ASTNode *newNode = (ASTNode *)malloc(sizeof(ASTNode));
    if (!newNode) { perror("Erro ao alocar memória para ASTNode"); exit(EXIT_FAILURE); }
    newNode->type = type;
    newNode->token = token;
    newNode->num_children = 0;
    newNode->line = (token != NULL) ? token->linha : 0;
    newNode->column = (token != NULL) ? token->coluna : 0;
    for (int i = 0; i < MAX_CHILDREN; i++) newNode->children[i] = NULL;
    return newNode;
}

void add_child(ASTNode *parent, ASTNode *child) {
    if (child == NULL) return;
    if (parent->num_children < MAX_CHILDREN) { parent->children[parent->num_children++] = child;
    } else { fprintf(stderr, "Erro: Número máximo de filhos excedido.\n"); }
}

void free_ast(ASTNode *node) {
    if (node == NULL) return;
    for (int i = 0; i < node->num_children; i++) { free_ast(node->children[i]); }
    free(node);
}

void print_ast(ASTNode *node, int indent) {
    if (node == NULL) return;
    for (int i = 0; i < indent; i++) printf("  ");
    
    printf("[%s]", node_type_string(node->type));
    if (node->token && node->token->atributo) {
        printf(" (%s)", node->token->atributo);
    }
    printf("\n");

    for (int i = 0; i < node->num_children; i++) {
        print_ast(node->children[i], indent + 1);
    }
}


// --- Funções do Parser ---
void init_parser(FILE *input_file) {
    yyin = input_file;
    fill_buffer();
}

void report_syntax_error(const char *expected) {
    fprintf(stderr, "Erro Sintático na linha %d, coluna %d: Esperado %s, mas encontrado '%s' (Tipo: %s)\n",
            lookahead_token->linha, lookahead_token->coluna, expected, lookahead_token->atributo, token_nome_string(lookahead_token->nome));
    exit(EXIT_FAILURE);
}

void match(nome_token expected_type) {
    if (lookahead_token == NULL || lookahead_token->nome == TOK_EOF) { 
        fprintf(stderr, "Erro: Fim de arquivo inesperado ao esperar por %s.\n", token_nome_string(expected_type));
        exit(EXIT_FAILURE); 
    }
    if (lookahead_token->nome == expected_type) {
        consume_token();
    } else {
        report_syntax_error(token_nome_string(expected_type));
    }
}

// --- Implementação das Regras Gramaticais ---

int is_next_a_declaration() {
    int k = 0;
    if (peek_token(k)->nome != TOK_ID) return 0;
    k++;
    while (peek_token(k)->nome == VIRGULA) {
        k++;
        if (peek_token(k)->nome != TOK_ID) return 0;
        k++;
    }
    if (peek_token(k)->nome == SETA) {
        return 1;
    }
    return 0;
}

ASTNode *parse_Programa() {
    ASTNode *node = create_node(NODE_PROGRAMA, NULL);
    match(TOK_MAIN);
    match(TOK_ID);
    match(ABRE_PARENT);
    match(FECHA_PARENT);
    add_child(node, parse_Bloco());
    return node;
}

ASTNode *parse_Bloco() {
    ASTNode *node = create_node(NODE_BLOCO, NULL);
    match(TOK_INICIO);
    add_child(node, parse_DeclaracaoVars());
    add_child(node, parse_SequenciaComandos());
    match(TOK_FIM);
    return node;
}

ASTNode *parse_DeclaracaoVars() {
    ASTNode *all_declarations = create_node(NODE_DECLARACAO_VARS, NULL);
    while (is_next_a_declaration()) {
        ASTNode *single_line = create_node(NODE_DECLARACAO_VARS, NULL);
        add_child(single_line, parse_ListaIds());
        match(SETA);
        add_child(single_line, parse_Tipo());
        match(PONTO_VIRGULA);
        add_child(all_declarations, single_line);
    }
    if (all_declarations->num_children > 0) {
        return all_declarations;
    }
    free_ast(all_declarations);
    return NULL;
}

ASTNode *parse_ListaIds() {
    ASTNode *node = create_node(NODE_LISTA_IDS, NULL);
    add_child(node, create_node(NODE_ID, lookahead_token));
    match(TOK_ID);
    add_child(node, parse_ListaIdsLinha());
    return node;
}

ASTNode *parse_ListaIdsLinha() {
    if (lookahead_token->nome == VIRGULA) {
        ASTNode *node = create_node(NODE_LISTA_IDS_LINHA, NULL);
        match(VIRGULA);
        add_child(node, create_node(NODE_ID, lookahead_token));
        match(TOK_ID);
        add_child(node, parse_ListaIdsLinha());
        return node;
    }
    return NULL;
}

ASTNode *parse_Tipo() {
    ASTNode *node = create_node(NODE_TIPO, lookahead_token);
    if (lookahead_token->nome == TOK_INT || lookahead_token->nome == TOK_CHAR || lookahead_token->nome == TOK_FLOAT) {
        match(lookahead_token->nome);
    } else {
        report_syntax_error("'int', 'char' ou 'float'");
    }
    return node;
}

ASTNode *parse_SequenciaComandos() {
    if (lookahead_token->nome == TOK_ID || lookahead_token->nome == TOK_CASO ||
        lookahead_token->nome == TOK_ENQUANTO || lookahead_token->nome == TOK_REPITA) {
        ASTNode *node = create_node(NODE_SEQUENCIA_COMANDOS, NULL);
        add_child(node, parse_Comando());
        ASTNode *next_seq = parse_SequenciaComandos();
        if (next_seq) add_child(node, next_seq);
        return node;
    }
    return NULL;
}

ASTNode *parse_Comando() {
    switch (lookahead_token->nome) {
        case TOK_ID:
            return parse_ComandoAtribuicao();
        case TOK_CASO:
            return parse_ComandoSelecao();
        case TOK_ENQUANTO:
        case TOK_REPITA:
            return parse_ComandoRepeticao();
        default:
            report_syntax_error("início de comando");
            return NULL;
    }
}

ASTNode *parse_ComandoAtribuicao() {
    ASTNode *node = create_node(NODE_COMANDO_ATRIBUICAO, NULL);
    add_child(node, create_node(NODE_ID, lookahead_token));
    match(TOK_ID);
    match(TOK_ASSIGN);
    add_child(node, parse_Expressao());
    match(PONTO_VIRGULA);
    return node;
}

ASTNode *parse_ComandoSelecao() {
    ASTNode *node = create_node(NODE_COMANDO_SELECAO, NULL);
    match(TOK_CASO);
    match(ABRE_PARENT);
    add_child(node, parse_Condicao());
    match(FECHA_PARENT);
    match(TOK_ENTAO);
    add_child(node, parse_ComandoOuBloco());
    add_child(node, parse_ParteSenao());
    return node;
}

ASTNode *parse_ParteSenao() {
    if (lookahead_token->nome == TOK_SENAO) {
        match(TOK_SENAO);
        return parse_ComandoOuBloco();
    }
    return NULL;
}

ASTNode *parse_ComandoOuBloco() {
    if (lookahead_token->nome == TOK_INICIO) {
        return parse_Bloco();
    }
    return parse_Comando();
}

ASTNode *parse_ComandoRepeticao() {
    ASTNode *node = create_node(NODE_COMANDO_REPETICAO, lookahead_token);
    if (lookahead_token->nome == TOK_ENQUANTO) {
        match(TOK_ENQUANTO);
        match(ABRE_PARENT);
        add_child(node, parse_Condicao());
        match(FECHA_PARENT);
        match(TOK_FACA);
        add_child(node, parse_ComandoOuBloco());
    } else if (lookahead_token->nome == TOK_REPITA) {
        match(TOK_REPITA);
        add_child(node, parse_ComandoOuBloco());
        match(TOK_ATE);
        match(ABRE_PARENT);
        add_child(node, parse_Condicao());
        match(FECHA_PARENT);
        match(PONTO_VIRGULA);
    }
    return node;
}

ASTNode *parse_Condicao() {
    ASTNode *node = create_node(NODE_CONDICAO, NULL);
    add_child(node, parse_Expressao());
    add_child(node, parse_OpRelacional());
    add_child(node, parse_Expressao());
    return node;
}

ASTNode *parse_OpRelacional() {
    ASTNode *node = create_node(NODE_OP_RELACIONAL, lookahead_token);
    if (lookahead_token->nome == TOK_RELOP) {
        match(TOK_RELOP);
    } else {
        report_syntax_error("operador relacional");
    }
    return node;
}

ASTNode *parse_Expressao() {
    ASTNode *termo_node = parse_Termo();
    return parse_ExpressaoLinha(termo_node);
}

ASTNode *parse_ExpressaoLinha(ASTNode *left_node) {
    if (lookahead_token->nome == TOK_ARTOP && (strcmp(lookahead_token->atributo, "+") == 0 || strcmp(lookahead_token->atributo, "-") == 0)) {
        ASTNode *op_node = create_node(NODE_OP_ARITMETICO, lookahead_token);
        match(TOK_ARTOP);
        add_child(op_node, left_node);
        add_child(op_node, parse_Termo());
        return parse_ExpressaoLinha(op_node);
    }
    return left_node;
}

ASTNode *parse_Termo() {
    ASTNode *fator_node = parse_Fator();
    return parse_TermoLinha(fator_node);
}

ASTNode *parse_TermoLinha(ASTNode *left_node) {
    if (lookahead_token->nome == TOK_ARTOP && (strcmp(lookahead_token->atributo, "*") == 0 || strcmp(lookahead_token->atributo, "/") == 0 || strcmp(lookahead_token->atributo, "^") == 0)) {
        ASTNode *op_node = create_node(NODE_OP_ARITMETICO, lookahead_token);
        match(TOK_ARTOP);
        add_child(op_node, left_node);
        add_child(op_node, parse_Fator());
        return parse_TermoLinha(op_node);
    }
    return left_node;
}

ASTNode *parse_Fator() {
    ASTNode *node;
    if (lookahead_token->nome == ABRE_PARENT) {
        match(ABRE_PARENT);
        node = parse_Expressao();
        match(FECHA_PARENT);
        return node;
    } else if (lookahead_token->nome == TOK_ID) {
        node = create_node(NODE_ID, lookahead_token);
        match(TOK_ID);
        return node;
    } else {
        return parse_Constante();
    }
}

ASTNode *parse_Constante() {
    ASTNode *node;
    switch (lookahead_token->nome) {
        case CONST_INT:
            node = create_node(NODE_CONST_INT, lookahead_token);
            match(CONST_INT);
            break;
        case CONST_FLOAT:
            node = create_node(NODE_CONST_FLOAT, lookahead_token);
            match(CONST_FLOAT);
            break;
        case CONST_CHAR:
            node = create_node(NODE_CONST_CHAR, lookahead_token);
            match(CONST_CHAR);
            break;
        default:
            report_syntax_error("constante");
            return NULL; 
    }
    return node;
}