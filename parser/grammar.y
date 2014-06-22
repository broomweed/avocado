%{
#include <stdio.h>
#include <string.h>
#include "avocado.h"

FILE *yyin;
extern int yychar;
int debug;

int yylex(void);
int yyparse(void);

scope *outermost;
scope *current_scope;

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
            fprintf(stderr, "Unrecognized flag %s\n", argv[1]);
            return 1;
        }
    } else {
        printf("usage: %s [-d] <file>\n", argv[0]);
        printf("\t-d:\trun in debug mode\n");
        return 1;
    }
    if (!yyin) {
        fprintf(stderr,
                "Couldn't open file %s. Are you sure it exists?\n",
                argv[argc-1]);
        return 1;
    }
    outermost = malloc(sizeof(scope));
    outermost->vars = NULL;
    outermost->outer = NULL;
    current_scope = outermost;
    if (debug) printf("==== PARSING PHASE ====\n");
    yyparse();
    return 0;
}

ast_node *root;

%}

%token TOKVAR TOKPRINT TOKIF TOKELSE TOKNOTHING TOKTRUE TOKFALSE TOKWHILE TOKDEF
%token EQ LTEQ GTEQ NE SEQ SLTEQ SGTEQ SLT SGT SNE AND OR NOT XOR
%token INCR DECR PLUSEQUALS MINUSEQUALS TIMESEQUALS DIVEQUALS CONCATEQUALS
%token UNARY_MINUS
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
%type <n> qualifiedblock
%type <n> statement
%type <n> singlestatement
%type <n> assignment
%type <n> declare
%type <n> newvar
%type <n> expr
%type <n> varname
%type <n> newvarname
%type <n> reassigner
%type <n> list
%type <n> comma_exprs

%left AND OR NOT XOR
%left '<' '>' EQ LTEQ GTEQ LT GT NE SEQ SLTEQ SGTEQ SLT SGT SNE
%left ':'
%left '+' '-'
%left '*' '/'
%right '^'
%left '!'
%left '['
%left UNARY_MINUS
/* expect 1 for the dangling else ambiguity */
%expect 1
%%
program: statementlist {
        root = $1;
        if (debug) printf("==== EVALUATION PHASE ====\n");
        if (debug) printf("Evaluating root AST node...\n");
        ast_eval_expr(root);
        if (debug) printf("\ndone.\n");
        fclose(yyin);
        if (debug) printf("==== CLEANUP PHASE ====\n");
        cleanup();
    }

statementlist: statement {
        if (debug) printf(": %c\n", $1->op);
        $$ = $1;
    } | statementlist statement {
        if (debug) printf(". %c\n", $2->op);
        $$ = node(MULTI, $1, $2);
    }

block:
    '{' statementlist '}' {
        $$ = node(ENCLOSED_SCOPE, $2, NULL);
    }

qualifiedblock:
    TOKIF expr statement {
        $$ = node(IF, $2, node(IFELSE, $3, NULL));
    } | TOKIF expr statement TOKELSE statement {
        $$ = node(IF, $2, node(IFELSE, $3, $5));
    } | TOKWHILE expr statement {
        $$ = node(WHILE, $2, $3);
    } | block {
        $$ = $1;
    }

statement:
    singlestatement ';' {
        $$ = $1;
    } | qualifiedblock {
        $$ = $1;
    }

singlestatement:
    assignment {
        $$ = $1;
    } | reassigner {
        $$ = $1;
    } | newvar {
        $$ = $1;
    } | declare {
        $$ = $1;
    } | TOKPRINT expr {
        $$ = node(PRINT, $2, NULL);
    }

assignment:
    newvarname '=' expr {
        $$ = node(ASSIGN, $1, $3);
    }

newvar:
    TOKVAR newvarname {
        $$ = node(CREATE, $2, NULL);
    }

declare:
    TOKVAR newvarname '=' expr {
        $$ = node(CREATE, $2, $4);
    }

newvarname:
    NAME {
        $$ = node_str($1);
    } | '`' expr '`' {
        $$ = node(VARNAME, $2, NULL);
    }

varname:
    NAME {
        $$ = node_name($1);
    } | '`' expr '`' {
        $$ = node(VARNAME, $2, NULL);
    }

expr:
    expr AND expr {
        $$ = node(BAND, $1, $3);
    } | expr OR expr {
        $$ = node(BOR, $1, $3);
    } | expr XOR expr {
        $$ = node(BXOR, $1, $3);
    } | '!' expr {
        $$ = node(BNOT, $2, NULL);
    } | expr '>' expr {
        $$ = node(NUM_GT, $1, $3);
    } | expr '<' expr {
        $$ = node(NUM_LT, $1, $3);
    } | expr EQ expr {
        $$ = node(NUM_EQ, $1, $3);
    } | expr LTEQ expr {
        $$ = node(NUM_LTEQ, $1, $3);
    } | expr GTEQ expr {
        $$ = node(NUM_GTEQ, $1, $3);
    } | expr NE expr {
        $$ = node(NUM_NE, $1, $3);
    } | expr SGT expr {
        $$ = node(STR_GT, $1, $3);
    } | expr SLT expr {
        $$ = node(STR_LT, $1, $3);
    } | expr SEQ expr {
        $$ = node(STR_EQ, $1, $3);
    } | expr SNE expr {
        $$ = node(STR_NE, $1, $3);
    } | expr SLTEQ expr {
        $$ = node(STR_LTEQ, $1, $3);
    } | expr SGTEQ expr {
        $$ = node(STR_GTEQ, $1, $3);
    } | expr ':' expr {
        $$ = node(CONCAT, $1, $3);
    } | expr '+' expr {
        $$ = node(ADD, $1, $3);
    } | expr '-' expr {
        $$ = node(SUB, $1, $3);
    } | expr '*' expr {
        $$ = node(MUL, $1, $3);
    } | expr '/' expr {
        $$ = node(DIV, $1, $3);
    } | '-' expr %prec UNARY_MINUS {
        $$ = node(SUB, node_int(0), $2);
    } | '+' expr %prec UNARY_MINUS {
        /* this could be useful to convert to number */
        $$ = node(ADD, node_int(0), $2);
    } | '(' expr ')' {
        $$ = $2;
    } | expr '[' expr ']' {
        $$ = node(ELEMENT, $1, $3);
    } | STRLIT {
        $$ = node_str($1);
    } | list {
        $$ = $1;
    } | varname {
        $$ = $1;
    } | INTEGER {
        $$ = node_int($1);
    } | FLOAT {
        $$ = node_dbl($1);
    } | TOKNOTHING {
        $$ = node_nothing();
    } | TOKTRUE {
        $$ = node_boolean(1);
    } | TOKFALSE {
        $$ = node_boolean(0);
    }

list:
    '[' comma_exprs ']' {
        $$ = $2;
    }

comma_exprs:
    expr {
        $$ = node(LISTEND, $1, NULL);
    } | comma_exprs ',' expr {
        $$ = node(LISTELEM, $3, $1);
    }

reassigner:
    newvarname INCR {
        $$ = node(COMPOUND, $1, node(ADD, NULL, node_int(1)));
    } | newvarname DECR {
        $$ = node(COMPOUND, $1, node(SUB, NULL, node_int(1)));
    } | newvarname PLUSEQUALS expr {
        $$ = node(COMPOUND, $1, node(ADD, NULL, $3));
    } | newvarname MINUSEQUALS expr {
        $$ = node(COMPOUND, $1, node(SUB, NULL, $3));
    } | newvarname TIMESEQUALS expr {
        $$ = node(COMPOUND, $1, node(MUL, NULL, $3));
    } | newvarname DIVEQUALS expr {
        $$ = node(COMPOUND, $1, node(DIV, NULL, $3));
    } | newvarname CONCATEQUALS expr {
        $$ = node(COMPOUND, $1, node(CONCAT, NULL, $3));
    }
%%
