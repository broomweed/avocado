%{
#include <stdio.h>
#include <string.h>
#include "avocado.h"

FILE *yyin;
extern int yychar;
int debug;

void yyerror(const char *str) {
    fprintf(stderr, "error: %s -- unexpected '%c'\n", str, yychar);
}

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    if (argc == 2) {
        yyin = fopen(argv[1], "r");
        debug = 0;
    } else if (argc == 3) {
        if (!strcmp(argv[1], "-d")) {
            debug = 1;
            yyin = fopen(argv[2], "r");
        } else {
            printf("Unrecognized flag %s", argv[1]);
            return 1;
        }
    } else {
        printf("usage: %s [-d] <file>\n", argv[0]);
        printf("\t-d:\trun in debug mode\n");
        return 1;
    }
    yyparse();
    return 0;
}

ast_node *root;

%}

%token TOKVAR TOKPRINT TOKIF TOKELSE TOKNOTHING TOKTRUE TOKFALSE TOKWHILE TOKDEF
%token EQ LTEQ GTEQ LT GT NE AND OR NOT XOR
%union
{
    int i;
    char *s;
    double d;
    struct ast_node *n;
}
%token <s> NAME
%token <i> INTEGER
%token <s> STRLIT
%token <d> FLOAT
%type <n> statementlist
%type <n> block
%type <n> cond
%type <n> test
%type <n> subtest
%type <n> qualifiedblock
%type <n> statement
%type <n> assignment
%type <n> declare
%type <n> newvar
%type <n> strexpr
%type <n> expr
%type <n> term
%type <n> factor
%type <n> varname
%type <n> varnamestr
%%
program: statementlist {
        if (debug) printf(". }\n");
        root = $1;
        if (debug) printf("Evaluating root AST node...\n");
        ast_eval_expr(root);
        if (debug) printf("\ndone.\n");
        fclose(yyin);
        cleanup();
    }

statementlist: statement {
        if (debug) printf("{ %c\n", $1->op);
        $$ = $1;
    } | statementlist statement {
        if (debug) printf(". %c\n", $2->op);
        $$ = node(BLOCK, $1, $2);
    }

block:
    '{' statementlist '}' {
        $$ = $2;
    }

qualifiedblock:
    TOKIF cond block {
        $$ = node(IF, $2, node(IFELSE, $3, NULL));
    } | TOKIF cond block TOKELSE qualifiedblock {
        $$ = node(IF, $2, node(IFELSE, $3, $5));
    } | TOKWHILE cond block {
        $$ = node(WHILE, $2, $3);
    } | block {
        $$ = $1;
    }

cond:
    cond AND test {
        $$ = node(BAND, $1, $3);
    } | cond OR test {
        $$ = node(BOR, $1, $3);
    } | cond XOR test {
        $$ = node(BXOR, $1, $3);
    } | test {
        $$ = $1;
    }

test:
    test '>' subtest {
        $$ = node(CMP_GT, $1, $3);
    } | test '<' subtest {
        $$ = node(CMP_LT, $1, $3);
    } | test EQ subtest {
        $$ = node(CMP_EQ, $1, $3);
    } | test LTEQ subtest {
        $$ = node(CMP_LTEQ, $1, $3);
    } | test GTEQ subtest {
        $$ = node(CMP_GTEQ, $1, $3);
    } | test NE subtest {
        $$ = node(CMP_NE, $1, $3);
    } | strexpr {
        $$ = $1;
    }

subtest:
    strexpr {
        $$ = $1;
    } | '!' subtest {
        $$ = node(BNOT, $2, NULL);
    } | '(' cond ')' {
        $$ = $2;
    }

statement:
    assignment ';' {
        $$ = $1;
    } | newvar ';' {
        $$ = $1;
    } | declare ';' {
        $$ = $1;
    } | TOKPRINT strexpr ';' {
        $$ = node(PRINT, $2, NULL);
    } | qualifiedblock {
        $$ = $1;
    }

assignment:
    varnamestr '=' strexpr {
        $$ = node(ASSIGN, $1, $3);
    }

newvar:
    TOKVAR varnamestr {
        $$ = node(CREATE, $2, NULL);
    }

declare:
    TOKVAR varnamestr '=' strexpr {
        $$ = node(CREATE, $2, $4);
    }

varnamestr:
    NAME {
        $$ = node_str($1);
    } | '`' strexpr '`' {
        $$ = node(VARNAME, $2, NULL);
    }

varname:
    NAME {
        $$ = node_name($1);
    } | '`' strexpr '`' {
        $$ = node(VARNAME, $2, NULL);
    }

strexpr:
    strexpr ':' expr {
        $$ = node(CONCAT, $1, $3);
    } | expr {
        $$ = $1;
    }

expr:
    expr '+' term {
        $$ = node(ADD, $1, $3);
    } | expr '-' term {
        $$ = node(SUB, $1, $3);
    } | term {
        $$ = $1;
    } | STRLIT {
        $$ = node_str($1);
    } | TOKNOTHING {
        $$ = node_nothing();
    } | TOKTRUE {
        $$ = node_boolean(1);
    } | TOKFALSE {
        $$ = node_boolean(0);
    }

term:
    term '*' factor {
        $$ = node(MUL, $1, $3);
    } | term '/' factor {
        $$ = node(DIV, $1, $3);
    } | factor {
        $$ = $1;
    }

factor:
    varname {
        $$ = $1;
    } | INTEGER {
        $$ = node_int($1);
    } | FLOAT {
        $$ = node_dbl($1);
    } | '(' expr ')' {
        $$ = $2;
    }
%%
