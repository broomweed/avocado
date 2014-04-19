#include <stdio.h>
#include "uthash.h"

enum vartypes {INT, DOUBLE, STRING, UNDEFINED};

typedef struct var {
    UT_hash_handle hh;
    char name[64];
    enum vartypes type;
    union content {
        int i;
        double d;
        char* s;
    } content;
    char *str_equiv;
} var;

enum asttypes {
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    CONCAT = ':',
    CREATE = 'v',
    ASSIGN = '=',
    BLOCK = '}',
    PRINT = 'p',
    VARNAME = '`',
    TERMINT = 'I',
    TERMSTR = 'S',
    TERMDBL = 'D',
    TERMNAME = 'N'
};

typedef struct ast_node {
    enum asttypes op;
    union {
        int termint;
        char *termstr;
        double termdbl;
        struct {
            struct ast_node *lhs;
            struct ast_node *rhs;
        } children;
    } content;
} ast_node;

extern ast_node *root;

extern int debug; // Debug flag

extern void setvar_str(char *name, char *val);
extern void setvar_double(char *name, double val);
extern void setvar_int(char *name, int val);
extern int getvar_int(char *name);
extern char *getvar_str(char *name);
extern double getvar_double(char *name);
extern var *addvar(char *name);
extern var *find_var(char *name);

extern var *newvar_int(int val);
extern var *newvar_str(char *str);
extern var *newvar_dbl(double val);
var *var_assign(char *name, var *value);

extern var *ast_eval_expr(ast_node *node);
extern ast_node *node(enum asttypes, ast_node *lhs, ast_node *rhs);
extern ast_node *node_int(int val);
extern ast_node *node_str(char *val);
extern ast_node *node_dbl(double val);
extern ast_node *node_name(char *val);

extern void free_node(ast_node *node);
extern void free_var(var *to_free);
extern void cleanup();

/* Var arithmetic/operators. */
extern var *vars_sum(var *v1, var *v2);
extern var *vars_diff(var *v1, var *v2);
extern var *vars_product(var *v1, var *v2);
extern var *vars_quotient(var *v1, var *v2);
extern var *vars_concat(var *v1, var *v2);

extern void print_var(char *str);
