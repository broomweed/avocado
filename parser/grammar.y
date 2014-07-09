%{
#include <stdio.h>
#include <string.h>
#include "avocado.h"
#define YYERROR_VERBOSE

FILE *yyin;
extern int yychar;
extern int yylineno;
int debug;
int yydebug = 1;

int yylex(void);
int yyparse(var **result);

scope *outermost;
scope *current_scope;
var **program_return_value;

int bracket_counts[32];
int interp_count;

void yyerror(var **result, const char *str) {
    throw_error(str, yylineno);
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
    interp_count = 0;
    outermost = malloc(sizeof(scope));
    outermost->vars = NULL;
    outermost->outer = NULL;
    outermost->last_val = NULL;
    outermost->is_eval = 0;
    current_scope = outermost;
    if (debug) printf("==== PARSING PHASE ====\n");
    program_return_value = malloc(sizeof(program_return_value));
    yyparse(program_return_value);
    if (yyin) fclose(yyin);
    cleanup();
    free_var(*program_return_value);
    free(program_return_value);
    //printf("%p", (void*)program_return_value);
    /*if (*program_return_value) {
        return (*program_return_value)->content.i;
    } else {*/
    return 0;
    /*}*/
}

%}
%parse-param { var **result }

%token VAR "var"
%token T_PRINT "print"
%token T_IF "if"
%token THEN "then"
%token ELSE "else"
%token T_WHILE "while"
%token DO "do"
%token DEF "def"
%token AS "as"
%token T_EVAL "eval"
%token T_NOTHING "nothing"
%token TRUE "true"
%token FALSE "false"
%token EQ "=="
%token LTEQ "<="
%token GTEQ ">="
%token NE "!="
%token SEQ "eq"
%token SLTEQ "le"
%token SGTEQ "ge"
%token SLT "lt"
%token SGT "gt"
%token SNE "ne"
%token AND "&&"
%token OR "||"
%token NOT "!"
%token XOR "xor"
%token INCR "++"
%token DECR "--"
%token PLUSEQUALS "+="
%token MINUSEQUALS "-="
%token TIMESEQUALS "*="
%token DIVEQUALS "/="
%token CONCATEQUALS ":="
%token OBRACE '{'
%token EBRACE '}'
%token INTERP_BEGIN
%token INTERP_END
%token UNARY_MINUS
%token END 0 "end-of-file"
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
%type <n> statement_list
%type <n> block
%type <n> qualified_block
%type <n> statement
%type <n> assignment
%type <n> declare
%type <n> newvar
%type <n> expr
%type <n> varname
%type <n> compound
%type <n> list
%type <n> function_def
%type <n> function_call
%type <n> function_params
%type <n> comma_names
%type <n> comma_exprs

%right PRINT_PREC
%right EVAL_PREC
%left FUNC_CALL
%left ','
%left COMMAS
%right '='
%left AND OR NOT XOR
%left '<' '>' EQ LTEQ GTEQ LT GT NE SEQ SLTEQ SGTEQ SLT SGT SNE
%left "+=" "-=" "*=" "/=" ":="
%left ':'
%nonassoc PAREN_FUNC_CALL
%left '+' '-'
%left '*' '/'
%right '^'
%left '!'
%left '['
%left UNARY_MINUS
%left '('
%left SINGLE_EXPR
%left NAMEPREC
%left INTERP_BEGIN INTERP_END
%nonassoc NAME T_NOTHING TRUE FALSE INTEGER STRLIT FLOAT '`'

%expect 2
/* 2 shift/reduce conflicts expected:
   the dangling else ambiguity; i.e. which if does the else apply to here?
        if x then
        if y then
        z();
        else
        w();
     (it assumes the else applies to 'if y,' to spare your wondering)
     there are 2 of these for some reason, I forget why
 */
%%
program: statement_list {
        ast_node *root = $1;
        if (debug) printf("==== EVALUATION PHASE ====\n");
        if (debug) printf("Evaluating root AST node...\n");
        if (root != NULL) {
            *result = ast_eval_expr(root);
        } else {
            *result = NULL;
        }
        if (debug) printf("\ndone.\n");
        if (debug) printf("==== CLEANUP PHASE ====\n");
        free_node(root);
    } | expr {
        ast_node *root = $1;
        if (debug) printf("---- Evaluating expression... ----");
        if (debug) printf("Evaluating root AST node...\n");
        if (root != NULL) {
            *result = ast_eval_expr(root);
        } else {
            *result = NULL;
        }
        if (debug) printf("\ndone.\n");
        if (debug) printf("---- Cleaning up expression. ----");
        free_node(root);
    }

statement_list: statement {
        if (debug) printf(": %c\n", $1->op);
        $$ = node(MULTI, $1, NULL);;
    } | statement_list statement {
        if (debug) printf("| %c\n", $2->op);
        $$ = node(MULTI, $1, $2);
    }

block:
    OBRACE statement_list EBRACE {
        $$ = node(ENCLOSED_SCOPE, $2, NULL);
    }

qualified_block:
    T_IF expr THEN statement {
        $$ = node(IF, $2, node(IFELSE, $4, NULL));
    } | T_IF expr block {
        $$ = node(IF, $2, node(IFELSE, $3, NULL));
    } | T_IF expr THEN statement ELSE statement {
        $$ = node(IF, $2, node(IFELSE, $4, $6));
    } | T_IF expr block ELSE statement {
        $$ = node(IF, $2, node(IFELSE, $3, $5));
    } | T_WHILE expr DO statement {
        $$ = node(WHILE, $2, $4);
    } | T_WHILE expr block {
        $$ = node(WHILE, $2, $3);
    } | block {
        $$ = $1;
    } | function_def {
        $$ = $1;
    }

statement:
    expr ';' {
        $$ = $1;
        yyerrok;
    } | qualified_block {
        $$ = $1;
        yyerrok;
    }

assignment:
    varname '=' expr {
        $$ = node(ASSIGN, $1, $3);
    }

newvar:
    VAR varname {
        $$ = node(CREATE, $2, NULL);
    }

declare:
    VAR varname '=' expr {
        $$ = node(CREATE, $2, $4);
    }

varname:
    NAME {
        $$ = node_str($1, yylineno);
    } | '`' expr '`' {
        $$ = node(VARNAME, $2, NULL);
    }

expr:
    expr INTERP_BEGIN expr INTERP_END expr {
        $$ = node(CONCAT, $1, node(CONCAT, $3, $5));
    } | assignment {
        $$ = $1;
    } | compound {
        $$ = $1;
    } | newvar {
        $$ = $1;
    } | declare {
        $$ = $1;
    } | T_PRINT expr %prec PRINT_PREC {
        $$ = node(PRINT, $2, NULL);
    } | expr AND expr {
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
        $$ = node(SUB, node_int(0, yylineno), $2);
    } | '+' expr %prec UNARY_MINUS {
        $$ = node(ADD, node_int(0, yylineno), $2);
    } | '(' expr ')' {
        $$ = $2;
    } | expr '[' expr ']' {
        $$ = node(ELEMENT, $1, $3);
    } | T_EVAL expr %prec EVAL_PREC {
        $$ = node(EVAL, $2, NULL);
    } | STRLIT {
        $$ = node_str($1, yylineno);
    } | list {
        $$ = $1;
    } | varname %prec NAMEPREC {
        $$ = node(VARNAME, $1, NULL);
    } | INTEGER {
        $$ = node_int($1, yylineno);
    } | FLOAT {
        $$ = node_dbl($1, yylineno);
    } | T_NOTHING {
        $$ = node_nothing(yylineno);
    } | TRUE {
        $$ = node_boolean(1, yylineno);
    } | FALSE {
        $$ = node_boolean(0, yylineno);
    } | function_call {
        $$ = $1;
    }

function_call:
    expr '(' comma_exprs ')' %prec PAREN_FUNC_CALL {
        $$ = node(FUNCCALL, $1, $3);
    } | varname comma_exprs %prec FUNC_CALL {
        $$ = node(FUNCCALL, node(VARNAME, $1, NULL), $2);
    } | expr '(' ')' %prec PAREN_FUNC_CALL {
        $$ = node(FUNCCALL, $1, node(LISTEND, NULL, NULL));
    }

list:
    '[' comma_exprs ']' {
        $$ = node(LISTEND, $2, NULL);
    } | '[' ']' {
        $$ = node(LISTEND, NULL, NULL);
    }

comma_exprs:
    expr %prec COMMAS {
        $$ = node(LISTEND, $1, NULL);
    } | comma_exprs ',' expr {
        $$ = node(LISTELEM, $3, $1);
    }

function_def:
    DEF varname function_params statement {
        $$ = node(CREATE, $2, node_function(
           ($4->op == ENCLOSED_SCOPE ? FUNC_BLOCK : 0), $3, $4));
    } | DEF varname function_params AS statement {
        $$ = node(CREATE, $2, node_function(
           ($5->op == ENCLOSED_SCOPE ? FUNC_BLOCK : 0), $3, $5));
    } | DEF varname block {
        $$ = node(CREATE, $2, node_function(FUNC_BLOCK, node(LISTEND, NULL, NULL), $3));
    } | DEF varname AS statement {
        $$ = node(CREATE, $2, node_function(
           ($4->op == ENCLOSED_SCOPE ? FUNC_BLOCK : 0), node(LISTEND, NULL, NULL), $4));
    }

function_params:
    '(' comma_names ')' {
        $$ = $2;
    } | comma_names {
        $$ = $1;
    } | '(' ')' {
        $$ = node(LISTEND, NULL, NULL);
    }

comma_names:
    varname {
        $$ = node(LISTEND, $1, NULL);
    } | comma_names ',' varname {
        $$ = node(LISTELEM, $3, $1);
    }

compound:
    varname INCR {
        $$ = node(COMPOUND, $1, node(ADD, NULL, node_int(1, yylineno)));
    } | varname DECR {
        $$ = node(COMPOUND, $1, node(SUB, NULL, node_int(1, yylineno)));
    } | varname PLUSEQUALS expr {
        $$ = node(COMPOUND, $1, node(ADD, NULL, $3));
    } | varname MINUSEQUALS expr {
        $$ = node(COMPOUND, $1, node(SUB, NULL, $3));
    } | varname TIMESEQUALS expr {
        $$ = node(COMPOUND, $1, node(MUL, NULL, $3));
    } | varname DIVEQUALS expr {
        $$ = node(COMPOUND, $1, node(DIV, NULL, $3));
    } | varname CONCATEQUALS expr {
        $$ = node(COMPOUND, $1, node(CONCAT, NULL, $3));
    }
%%
