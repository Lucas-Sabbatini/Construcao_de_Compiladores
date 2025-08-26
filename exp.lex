%{
#include <stdio.h>
#include <string.h>
#include "exp.h"

int yycolumn = 1;

#define YY_USER_ACTION yycolumn = yycolumn + yyleng;
#define YY_DECL Token* yylex(void)
%}

%option noyywrap

ID          [a-zA-Z_][a-zA-Z0-9_]*

INT         [0-9]+
FLOAT       {INT}(\.{INT})?([Ee][+-]?{INT})?|\.{INT}([Ee][+-]?{INT})?
CHAR        '[^']'
REL_OP      >|<|>=|<=|==|!=
ART_OP      \+|-|\*|\/|\^

ASSIGN      =
SETA        ->
COMMENT     "/*"([^*]|(\*+[^*/]))*\*+"/"

NEWLINE     \n
SEPARATOR   [ \t]+

%%

{SEPARATOR}     { /* Ignora */ }
{COMMENT}       { /* Ignora */ }
{NEWLINE}       { yylineno++; yycolumn = 1; }

"main"          { return criar_token(TOK_MAIN, "none", yylineno, yycolumn - yyleng); }
"inicio"        { return criar_token(TOK_INICIO, "none", yylineno, yycolumn - yyleng); }
"fim"           { return criar_token(TOK_FIM, "none", yylineno, yycolumn - yyleng); }
"int"           { return criar_token(TOK_INT, "none", yylineno, yycolumn - yyleng); }
"char"          { return criar_token(TOK_CHAR, "none", yylineno, yycolumn - yyleng); }
"float"         { return criar_token(TOK_FLOAT, "none", yylineno, yycolumn - yyleng); }
"caso"          { return criar_token(TOK_CASO, "none", yylineno, yycolumn - yyleng); }
"entao"         { return criar_token(TOK_ENTAO, "none", yylineno, yycolumn - yyleng); }
"senao"         { return criar_token(TOK_SENAO, "none", yylineno, yycolumn - yyleng); }
"enquanto"      { return criar_token(TOK_ENQUANTO, "none", yylineno, yycolumn - yyleng); }
"faca"          { return criar_token(TOK_FACA, "none", yylineno, yycolumn - yyleng); }
"repita"        { return criar_token(TOK_REPITA, "none", yylineno, yycolumn - yyleng); }
"ate"           { return criar_token(TOK_ATE, "none", yylineno, yycolumn - yyleng); }

{ASSIGN}        { return criar_token(TOK_ASSIGN, "none", yylineno, yycolumn - yyleng); }
{REL_OP}        { return criar_token(TOK_RELOP, yytext, yylineno, yycolumn - yyleng); }
{ART_OP}        { return criar_token(TOK_ARTOP, yytext, yylineno, yycolumn - yyleng);}
{ID}            { return criar_token(TOK_ID, yytext, yylineno, yycolumn - yyleng); }
{INT}           { return criar_token(CONST_INT, yytext, yylineno, yycolumn - yyleng); }
{FLOAT}         { return criar_token(CONST_FLOAT, yytext, yylineno, yycolumn - yyleng); }
{CHAR}          { return criar_token(CONST_CHAR, yytext, yylineno, yycolumn - yyleng); }
"("             { return criar_token(ABRE_PARENT, "none", yylineno, yycolumn - yyleng); }
")"             { return criar_token(FECHA_PARENT, "none", yylineno, yycolumn - yyleng); }
";"             { return criar_token(PONTO_VIRGULA, "none", yylineno, yycolumn - yyleng); }
","             { return criar_token(VIRGULA, "none", yylineno, yycolumn - yyleng); }
{SETA}          { return criar_token(SETA, "none", yylineno, yycolumn - yyleng); }

<<EOF>>         { return criar_token(TOK_EOF, "none", yylineno, yycolumn); }

.               { return criar_token(TOK_ERROR, yytext, yylineno, yycolumn - yyleng); }

%%