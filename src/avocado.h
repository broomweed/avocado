#include <stdio.h>
#include "uthash.h"

enum vartypes {INT, DOUBLE, STRING, BOOLEAN, UNDEFINED, NOTHING};

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
    ASSIGN = '_',
    BLOCK = '}',
    IF = 'i',
    IFELSE = 'e',
    WHILE = 'w',
    BAND = '&',
    BOR = '|',
    BNOT = '!',
    BXOR = '1', // as in '1 only'
    /* CMP_ because you can't name
       two enumerations the same thing,
       ever, anywhere... C, man */
    CMP_GT = '>',
    CMP_LT = '<',
    CMP_GTEQ = '(',
    CMP_LTEQ = ')',
    CMP_EQ = '=',
    CMP_NE = '#',
    PRINT = 'p',
    VARNAME = '`',
    TERMINT = 'I',
    TERMSTR = 'S',
    TERMDBL = 'D',
    TERMNAME = 'N',
    TERMBOOLEAN = 'B',
    EMPTY = ' ',
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

extern void setvar_str_fv(var *var, char *val);
extern void setvar_double_fv(var *var, double val);
extern void setvar_int_fv(var *var, int val);
extern void setvar_boolean_fv(var *var, int val);

extern int getvar_int(char *name);
extern char *getvar_str(char *name);
extern double getvar_double(char *name);
extern int getvar_boolean(char *name);

extern int getvar_int_fv(var *var);
extern char *getvar_str_fv(var *var);
extern double getvar_double_fv(var *var);
extern int getvar_boolean_fv(var *var);

extern var *addvar(char *name);
extern var *find_var(char *name);

extern var *ast_eval_expr(ast_node *node);
extern ast_node *node(enum asttypes type, ast_node *lhs, ast_node *rhs);
extern ast_node *node_int(int val);
extern ast_node *node_str(char *val);
extern ast_node *node_dbl(double val);
extern ast_node *node_name(char *val);
extern ast_node *node_nothing();
extern ast_node *node_boolean(int val);

extern void free_node(ast_node *node);
extern var *alloc_var();
extern void free_var(var *to_free);
extern void cleanup();

extern var *newvar_int(int val);
extern var *newvar_str(char *str);
extern var *newvar_dbl(double val);
extern var *newvar_boolean(int val);
extern var *newvar_nothing();
extern var *var_assign(char *name, var *value);

extern var *vars_sum(var *v1, var *v2);
extern var *vars_diff(var *v1, var *v2);
extern var *vars_product(var *v1, var *v2);
extern var *vars_quotient(var *v1, var *v2);
extern var *vars_concat(var *v1, var *v2);
extern var *var_test(var *v);

extern void print_var(char *str);

extern char *str_dup(char *str);
