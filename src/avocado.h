#include <stdio.h>
#include "uthash.h"
#define node(x, y, z) (real_node((x), (y), (z), (yylineno)))
#define node_function(x, y, z) (real_node_function((x), (y), (z), (yylineno)))
#define error(x) throw_error((x), line_num)

struct var;
struct function;

/* A dynamic array. */
typedef struct list {
    int max_size;
    int min_index;
    int size;
    struct var* contents;
} list;

enum vartypes {INT, DOUBLE, STRING, BOOLEAN, LIST, FUNCTION, UNDEFINED, NOTHING};

typedef struct var {
    int bound;
    enum vartypes type;
    union content {
        int i;
        double d;
        char* s;
        list* l;
        struct function *f;
    } content;
    char *str_equiv;
} var;

/* This binds a name to a variable in a scope. */
typedef struct binding {
    UT_hash_handle hh;
    char name[64];
    var *var;
} binding;

/* A linked list of nested scopes. This
   struct represents a single scope. */
typedef struct scope {
    /* This is the scope's enclosing scope. */
    struct scope *outer;
    /* This represents the bindings for the scope. */
    binding *vars;
    /* This is the value of the last expression
       executed within the scope; it is also set
       on function return. */
    var *last_val;
    /* This represents whether or not the current scope
       is being evaluated within an EVAL statement. */
    int is_eval;
} scope;

extern scope *outermost;
extern scope *current_scope;

enum asttypes {
    EVAL = '\'',
    ADD = '+',
    SUB = '-',
    MUL = '*',
    DIV = '/',
    CONCAT = ':',
    ELEMENT = '[',
    FUNCDEF = 'f',
    FUNCCALL = '(',
    EXPR = '$',
    CREATE = 'v',
    ASSIGN = '_',
    COMPOUND = '\\',
    MULTI = 'T', // like a linked list
    IF = 'i',
    IFELSE = 'e',
    WHILE = 'w',
    BAND = '&',
    BOR = '|',
    BNOT = '!',
    BXOR = '1', // as in '1 only'
    NUM_GT = '>',
    NUM_LT = '<',
    NUM_GTEQ = ']',
    NUM_LTEQ = '}',
    NUM_EQ = '=',
    NUM_NE = '#',
    STR_GT = 'g',
    STR_LT = 'l',
    STR_GTEQ = 'G',
    STR_LTEQ = 'L',
    STR_EQ = 'E',
    STR_NE = 'X',
    PRINT = 'p',
    VARNAME = '`',
    LISTELEM = ',',
    LISTEND = '@',
    TERMINT = 'I',
    TERMSTR = 'S',
    TERMDBL = 'D',
    TERMNAME = 'N',
    TERMBOOLEAN = 'B',
    EMPTY = ' ',
    ENCLOSED_SCOPE = '{',
};

enum flags {
    FUNC_BLOCK = 1,
};

typedef struct ast_node {
    enum asttypes op;
    int line_num;
    /* Flags indicate something special about
       this node. Usually unused. Right now,
       only functions use it to indicate whether
       or not they need their own special scope. */
    enum flags flags;
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

/* This represents a function that has
   been defined by the script. */
typedef struct function {
    /* A list of strings (in vars) that
       contain the names of parameters. */
    list *parameters;
    /* The AST node that will be executed when
       the function will be called. */
    struct ast_node *exec;
    enum flags flags;
} function;

extern ast_node *root;

extern int debug; // Debug flag

extern void throw_error(const char *msg, int line_num);

extern void setvar_str_fv(var *var, char *val);
extern void setvar_double_fv(var *var, double val);
extern void setvar_int_fv(var *var, int val);
extern void setvar_boolean_fv(var *var, int val);
void setvar_list_fv(var *var, list *val);

extern int getvar_int(char *name);
extern char *getvar_str(char *name);
extern double getvar_double(char *name);
extern int getvar_boolean(char *name);
extern list *getvar_list(char *name);

extern int getvar_int_fv(var *var);
extern char *getvar_str_fv(var *var);
extern double getvar_double_fv(var *var);
extern int getvar_boolean_fv(var *var);
list *getvar_list_fv(var *var);

extern var *addvar(char *name);
extern var *find_var(char *name);

extern var *ast_eval_expr(ast_node *node);
extern ast_node *real_node(enum asttypes type, ast_node *lhs, ast_node *rhs, int line_num);
extern ast_node *node_int(int val, int line_num);
extern ast_node *node_str(char *val, int line_num);
extern ast_node *node_dbl(double val, int line_num);
extern ast_node *node_name(char *val, int line_num);
extern ast_node *node_nothing(int line_num);
extern ast_node *node_boolean(int val, int line_num);
ast_node *ast_copy(ast_node *node);

extern void free_node(ast_node *node);
extern var *alloc_var();
extern void free_var(var *to_free);
extern void cleanup();

extern var *newvar_int(int val);
extern var *newvar_str(char *str);
extern var *newvar_dbl(double val);
extern var *newvar_boolean(int val);
extern var *newvar_list(list *val);
extern var *newvar_empty_list();
var *newvar_func(list *param_names, ast_node *exec, enum flags flags);
extern var *newvar_nothing();

extern void bind(char *name, var *value);
var *var_assign_fv(var *new, var *value);

extern var *vars_sum(var *v1, var *v2);
extern var *vars_diff(var *v1, var *v2);
extern var *vars_product(var *v1, var *v2);
extern var *vars_quotient(var *v1, var *v2);
extern var *vars_concat(var *v1, var *v2);
extern var *var_test(var *v);

extern void print_var(char *str);

extern char *str_dup(char *str);

extern char *escape_chars(char *str);

extern void new_scope();
extern void new_eval_scope();
extern void pop_scope();

extern int line_num;

/* --- from list.c --- */

extern list *list_push (list* target, var* value);
extern var *list_pop(list* target);
extern var *list_shift(list *target);
extern void list_copy(list* dest, list* src);
extern var *element_at(list* target, int index);
extern int set_element(list *target, int index, var *value);
extern list *alloc_list();
extern list *alloc_list_size(int size);
extern void free_list(list *l);
extern void var_copy (var *dest, var *src);

/* --- from functions.c --- */

extern void free_func(function *f);
extern function *func_copy(function *src);
extern function *create_func(list *parameters, ast_node *exec, enum flags flags);
extern var *call_func(function *func, list *args);
extern ast_node *real_node_function(int flags, ast_node *lhs, ast_node *rhs, int line_num);
