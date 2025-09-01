%{
#include <stdio.h>
#include <string.h>
#include "exp.h"

int yycolumn = 1;

#define YY_USER_ACTION yycolumn = yycolumn + yyleng;
#define YY_DECL Token* yylex(void)
%}

%option noyywrap

/* Definições de padrões */
ID          [a-zA-Z_][a-zA-Z0-9_]*
INT         [0-9]+
FLOAT       {INT}(\.{INT})?([Ee][+-]?{INT})?|\.{INT}([Ee][+-]?{INT})?
CHAR        '[^']'
REL_OP      >|<|>=|<=|==|!=
ART_OP      [+\-*/^]
SETA        ->
ASSIGN      =
COMMENT     "/*"([^*]|(\*+[^*/]))*\*+"/"
NEWLINE     \n
SEPARATOR   [ \t]+

%%

{SEPARATOR}     { /* Ignora */ }
{COMMENT}       { /* Ignora */ }
{NEWLINE}       { yylineno++; yycolumn = 1; }

"main"          { return criar_token(TOK_MAIN, "main", yylineno, yycolumn - yyleng); }
"inicio"        { return criar_token(TOK_INICIO, "inicio", yylineno, yycolumn - yyleng); }
"fim"           { return criar_token(TOK_FIM, "fim", yylineno, yycolumn - yyleng); }
"int"           { return criar_token(TOK_INT, "int", yylineno, yycolumn - yyleng); }
"char"          { return criar_token(TOK_CHAR, "char", yylineno, yycolumn - yyleng); }
"float"         { return criar_token(TOK_FLOAT, "float", yylineno, yycolumn - yyleng); }
"caso"          { return criar_token(TOK_CASO, "caso", yylineno, yycolumn - yyleng); }
"entao"         { return criar_token(TOK_ENTAO, "entao", yylineno, yycolumn - yyleng); }
"senao"         { return criar_token(TOK_SENAO, "senao", yylineno, yycolumn - yyleng); }
"enquanto"      { return criar_token(TOK_ENQUANTO, "enquanto", yylineno, yycolumn - yyleng); }
"faca"          { return criar_token(TOK_FACA, "faca", yylineno, yycolumn - yyleng); }
"repita"        { return criar_token(TOK_REPITA, "repita", yylineno, yycolumn - yyleng); }
"ate"           { return criar_token(TOK_ATE, "ate", yylineno, yycolumn - yyleng); }

{SETA}          { return criar_token(SETA, "->", yylineno, yycolumn - yyleng); }
{REL_OP}        { return criar_token(TOK_RELOP, yytext, yylineno, yycolumn - yyleng); }
{ASSIGN}        { return criar_token(TOK_ASSIGN, "=", yylineno, yycolumn - yyleng); }
{ART_OP}        { return criar_token(TOK_ARTOP, yytext, yylineno, yycolumn - yyleng); }

{ID}            { return criar_token(TOK_ID, yytext, yylineno, yycolumn - yyleng); }
{INT}           { return criar_token(CONST_INT, yytext, yylineno, yycolumn - yyleng); }
{FLOAT}         { return criar_token(CONST_FLOAT, yytext, yylineno, yycolumn - yyleng); }
{CHAR}          { return criar_token(CONST_CHAR, yytext, yylineno, yycolumn - yyleng); }

"("             { return criar_token(ABRE_PARENT, "(", yylineno, yycolumn - yyleng); }
")"             { return criar_token(FECHA_PARENT, ")", yylineno, yycolumn - yyleng); }
";"             { return criar_token(PONTO_VIRGULA, ";", yylineno, yycolumn - yyleng); }
","             { return criar_token(VIRGULA, ",", yylineno, yycolumn - yyleng); }

<<EOF>>         { return criar_token(TOK_EOF, "EOF", yylineno, yycolumn); }
.               { return criar_token(TOK_ERROR, yytext, yylineno, yycolumn - yyleng); }

%%


