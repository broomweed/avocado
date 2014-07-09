#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"
#include "avocado.h"
#include "y.tab.h"

extern scope *outermost;
extern scope *current_scope;
//extern int yylineno;
extern var *eval_string(char *str);
int line_num;

/* ------function prototypes------ */

/* var-setting by name */
void setvar_str(char *name, char *val);
void setvar_double(char *name, double val);
void setvar_int(char *name, int val);
void setvar_boolean(char *name, int val);
void setvar_list(char *name, list *val);

/* var-setting by pointer */
void setvar_str_fv(var *var, char *val);
void setvar_double_fv(var *var, double val);
void setvar_int_fv(var *var, int val);
void setvar_boolean_fv(var *var, int val);
void setvar_list_fv(var *var, list *val);
void setvar_function_fv(var *var, function *val);

/* var-getting by name */
int getvar_int(char *name);
char *getvar_str(char *name);
double getvar_double(char *name);
int getvar_boolean(char *name);
list *getvar_list(char *name);

/* var-getting by pointer */
int getvar_int_fv(var *var);
char *getvar_str_fv(var *var);
double getvar_double_fv(var *var);
int getvar_boolean_fv(var *var);
list *getvar_list_fv(var *var);
function *getvar_function_fv(var *var);

/* var stuff */
var *addvar(char *name);
var *find_var(char *name);

/* ast stuff */
var *ast_eval_expr(ast_node *node);
ast_node *real_node(enum asttypes type, ast_node *lhs, ast_node *rhs, int line_num);
ast_node *node_int(int val, int line_num);
ast_node *node_str(char *val, int line_num);
ast_node *node_dbl(double val, int line_num);
ast_node *node_name(char *val, int line_num);
ast_node *node_boolean(int val, int line_num);
ast_node *node_nothing(int line_num);
ast_node *ast_copy(ast_node *node);

/* mem stuff */
void free_node(ast_node *node);
var *alloc_var();
void free_var(var *to_free);
void clear_var_ptrs(var *to_free);
void unbind(binding *to_free);
void cleanup();

/* new-var code */
var *newvar_int(int val);
var *newvar_str(char *str);
var *newvar_dbl(double val);
var *newvar_boolean(int val);
var *newvar_list(list *val);
var *newvar_empty_list();
var *newvar_nothing();
var *newvar_func(list *param_names, ast_node *exec, enum flags flags);
var *var_assign(char *name, var *value);
var *var_assign_fv(var *new, var *value);

/* var arithmetic/operators */
var *vars_sum(var *v1, var *v2);
var *vars_diff(var *v1, var *v2);
var *vars_product(var *v1, var *v2);
var *vars_quotient(var *v1, var *v2);
var *vars_concat(var *v1, var *v2);
var *vars_cmp(var *v1, var *v2, enum asttypes type);

/* function that apparently doesn't exist in GNU library */
char *str_dup(char *str);

/* ------function definitions------ */

void error (char *msg) {
    fprintf(stderr, "%s near line %d\n", msg, line_num);
}

void setvar_str(char *name, char *val) {
    var *to_set = find_var(name);
    setvar_str_fv(to_set, val);
}

void setvar_double(char *name, double val) {
    var *to_set = find_var(name);
    setvar_double_fv(to_set, val);
}

void setvar_int(char *name, int val) {
    var *to_set = find_var(name);
    setvar_int_fv(to_set, val);
}

void setvar_boolean(char *name, int val) {
    var *to_set = find_var(name);
    setvar_boolean_fv(to_set, val);
}

void setvar_list(char *name, list *val) {
    var *to_set = find_var(name);
    setvar_list_fv(to_set, val);
}

void setvar_function(char *name, function *val) {
    var *to_set = find_var(name);
    setvar_function_fv(to_set, val);
}

void setvar_str_fv(var *to_set, char *val) {
    clear_var_ptrs(to_set);
    to_set->content.s = (char*)malloc((strlen(val)+1)*sizeof(char));
    strcpy(to_set->content.s, val);
    to_set->type = STRING;
}

void setvar_double_fv(var *to_set, double val) {
    clear_var_ptrs(to_set);
    to_set->content.d = val;
    to_set->type = DOUBLE;
}

void setvar_int_fv(var *to_set, int val) {
    clear_var_ptrs(to_set);
    to_set->content.i = val;
    to_set->type = INT;
}

void setvar_boolean_fv(var *to_set, int val) {
    clear_var_ptrs(to_set);
    if (val) to_set->content.i = 1;
    else to_set->content.i = 0;
    to_set->type = BOOLEAN;
}

void setvar_list_fv(var *to_set, list *val) {
    clear_var_ptrs(to_set);
    to_set->content.l = alloc_list_size(val->size);
    list_copy(to_set->content.l, val);
    to_set->type = LIST;
}

void setvar_function_fv(var *to_set, function *val) {
    clear_var_ptrs(to_set);
    to_set->content.f = func_copy(val);
    to_set->type = FUNCTION;
}

void make_var_nothing(var *find) {
    if (find->type == STRING) {
        free(find->content.s);
    }
    find->type = NOTHING;
    find->content.i = 0;
}

int getvar_int(char *name) {
    var *find = find_var(name);
    return getvar_int_fv(find);
}

char *getvar_str(char *name) {
    var *find = find_var(name);
    return getvar_str_fv(find);
}

double getvar_double(char *name) {
    var *find = find_var(name);
    return getvar_double_fv(find);
}

int getvar_boolean(char *name) {
    var *find = find_var(name);
    return getvar_boolean_fv(find);
}

list *getvar_list(char *name) {
    var *find = find_var(name);
    return getvar_list_fv(find);
}

function *getvar_function(char *name) {
    var *find = find_var(name);
    return getvar_function_fv(find);
}

int getvar_int_fv(var *find) {
    if (find == NULL) return 0;
    else if (find->type == INT || find->type == BOOLEAN) return find->content.i;
    else if (find->type == DOUBLE) return (int)find->content.d;
    else if (find->type == STRING) return atoi(find->content.s);
    else return 0;
}

char *getvar_str_fv(var *find) {
    if (find == NULL) {
        return NULL;
    }
    if (find->str_equiv != NULL) {
        free(find->str_equiv);
        find->str_equiv = NULL;
    }
    if (find->type == UNDEFINED) {
        find->str_equiv = malloc(10*sizeof(char));
        sprintf(find->str_equiv, "undefined");
    } else if (find->type == STRING) {
        return find->content.s;
    } else if (find->type == LIST) {
        int len = 0;
        for (int i = 0; i < find->content.l->size; i++) {
            len += strlen(getvar_str_fv(element_at(find->content.l, i))) + 1;
        }
        if (len > 0) {
            /* there's no +1 here because it adds +1 for the last space;
               but we don't put a last space, so we can use that spot
               for the terminating \0 */
            find->str_equiv = malloc((2+len) * sizeof(char));
            sprintf(find->str_equiv, "L:");
            len = 2;
            for (int i = 0; i < find->content.l->size; i++) {
                if (i == find->content.l->size-1) {
                    sprintf(find->str_equiv + len, "%s", getvar_str_fv(element_at(find->content.l, i)));
                } else {
                    sprintf(find->str_equiv + len, "%s ", getvar_str_fv(element_at(find->content.l, i)));
                }
                len += strlen(getvar_str_fv(element_at(find->content.l, i))) + 1;
            }
        } else {
            /* return an empty string for an empty list */
            find->str_equiv = malloc(sizeof(char));
            find->str_equiv[0] = '\0';
        }
    } else {
        find->str_equiv = malloc(16*sizeof(char));
        if (find->type == INT) {
            sprintf(find->str_equiv, "%d", find->content.i);
        } else if (find->type == DOUBLE) {
            sprintf(find->str_equiv, "%g", find->content.d);
        } else if (find->type == BOOLEAN) {
            if (find->content.i)
                sprintf(find->str_equiv, "true");
            else
                sprintf(find->str_equiv, "false");
        } else {
            sprintf(find->str_equiv, "???");
        }
    }
    return find->str_equiv;
}

double getvar_double_fv(var *find) {
    if (find == NULL) return 0.0f;
    else if (find->type == STRING) return atof(find->content.s);
    else if (find->type == INT || find->type == BOOLEAN) return (double)find->content.i;
    else if (find->type == DOUBLE) return find->content.d;
    else if (find->type == LIST) return (double)find->content.l->size;
    else return 0.0f;
}

int getvar_boolean_fv(var *find) {
    if (find == NULL) return 0;
    else if (find->type == NOTHING) return 0;
    else if (find->type == BOOLEAN && find->content.i == 0) return 0;
    else if (find->type == INT && find->content.i == 0) return 0;
    else if (find->type == DOUBLE && find->content.d == 0) return 0;
    else if (find->type == LIST && find->content.l->size == 0) return 0;
    else return 1;
}

list *getvar_list_fv(var *find) {
    if (find->type == LIST) return find->content.l;
    else {
        printf("Request for element in non-list.\n");
        list *x = alloc_list_size(1);
        list_push(x, find);
        return x;
    }
}

function *getvar_function_fv(var *find) {
    if (find->type == FUNCTION) return find->content.f;
    else {
        error("Cannot call a non-function");
        function *x = malloc(sizeof(function));
        x->parameters = NULL;
        x->exec = NULL;
        return x;
    }
}

var *addvar(char *name) {
    var *to_add = (var*)malloc(sizeof(var));
    binding *new_binding = malloc(sizeof(binding));
    if (to_add == NULL) {
        printf("Couldn't create variable %s: out of memory!\n", name);
        return NULL;
    }
    strncpy(new_binding->name, name, 64);
    new_binding->var = to_add;
    to_add->type = UNDEFINED;
    to_add->str_equiv = NULL;
    to_add->bound = 1;
    HASH_ADD_STR(current_scope->vars, name, new_binding);
    return to_add;
}

var *find_var(char *name) {
    binding *found = NULL;
    scope *searching_in = current_scope;
    if (!searching_in && debug) {
        fprintf(stderr, "what??\n");
        return NULL;
    }
    do {
        HASH_FIND_STR(searching_in->vars, name, found);
        searching_in = searching_in->outer;
    } while (found == NULL && searching_in != NULL);
    if (found != NULL) {
        return found->var;
    } else {
        return NULL;
    }
}

var *ast_eval_expr(ast_node *node) {
    var *lh, *rh, *new;
    var *to_ret = NULL;
    if (node == NULL) return NULL;
    line_num = node->line_num;
    if (debug) printf("NODE: %c\t\t: ", node->op);
    switch(node->op) {
        /* These operations do not act directly on variables. */
        case TERMINT:
            if (debug) printf("it's an int!\n");
            return newvar_int(node->content.termint);
        case TERMSTR:
            if (debug) printf("it's a string! (at %p)\n", node->content.termstr);
            return newvar_str(node->content.termstr);
        case TERMDBL:
            if (debug) printf("it's a double!\n");
            return newvar_dbl(node->content.termdbl);
        case TERMNAME:
            if (debug) printf("it's a var name!\n");
            to_ret = find_var(node->content.termstr);
            if (to_ret == NULL) {
                printf("--!-- %s: no such variable\n", node->content.termstr);
                return newvar_int(0);
            }
            return to_ret;
        case EMPTY:
            if (debug) printf("(empty)\n");
            return newvar_nothing();
        case TERMBOOLEAN:
            if (debug) printf("it's a boolean!\n");
            return newvar_boolean(node->content.termint);
        case ENCLOSED_SCOPE:
            if (debug) printf("{{{\n");
            new_scope();
            lh = ast_eval_expr(node->content.children.lhs);
            if (debug) printf("SCOPE END\t: }}}\n");
            pop_scope();
            return lh;
        case FUNCDEF:
            if (debug) printf("def.\n");
            /* LHS of FUNCDEF is a LIST of parameter names.
               RHS is an ast_node representing what happens when you call it.
               'def' wraps this node in an ASSIGN node so it gets a name.
               This same node type can be used in the future for anonymous functions. */
            /* Now, evaluate the name list... */
            lh = ast_eval_expr(node->content.children.lhs);
            /* And create a new function that has it and the RHS (which will be copied.) */
            rh = newvar_func(lh->content.l, node->content.children.rhs, node->flags);
            printf("FLAGS: %d\n", rh->content.f->flags);
            free(lh);
            return rh;
        case MULTI:
            if (debug) printf("MULTI...\n");
            ast_eval_expr(node->content.children.lhs);
            return ast_eval_expr(node->content.children.rhs);
        case COMPOUND:
            if (debug) printf("compound assignment of:\n");
            /* compound assignment */
            /* the LHS of compound assignment is the name of the variable;
               the RHS is an operation with a null RHS. */
            /* assign the name to the lhs of the other statement (which should be NULL) */
            node->content.children.rhs->content.children.lhs =
                node_name(node->content.children.lhs->content.termstr, line_num);
            /* evaluate it and assign the result to the LHS of this statement */
            lh = ast_eval_expr(node->content.children.lhs);
            rh = ast_eval_expr(node->content.children.rhs);
            var_assign_fv(find_var(lh->content.s), rh);
            /* set the LHS of the other statement back to null so we don't free the pointer twice */
            free(node->content.children.rhs->content.children.lhs);
            free_var(lh);
            free_var(rh);
            node->content.children.rhs->content.children.lhs = NULL;
            return NULL;
        case IF:
            /* The control flow constructs go here because they need control over
               which/how many times to evaluate a node, rather than evaluating both
               and doing something to them. */
            if (debug) printf("If.\n");
            lh = ast_eval_expr(node->content.children.lhs);
            if (getvar_boolean_fv(lh)) {
                to_ret = ast_eval_expr(node->content.children.rhs->content.children.lhs);
            } else {
                to_ret = ast_eval_expr(node->content.children.rhs->content.children.rhs);
            }
            if (!lh->bound) free_var(lh);
            return to_ret;
        case WHILE:
            if (debug) printf("While.\n");
            lh = ast_eval_expr(node->content.children.lhs);
            while (getvar_boolean_fv(lh)) {
                ast_eval_expr(node->content.children.rhs);
                if (!lh->bound) free_var(lh);
                lh = ast_eval_expr(node->content.children.lhs);
            }
            if (!lh->bound) free_var(lh);
            return NULL;
        default:
            if (debug) printf("...\n");
            if (node->content.children.lhs == NULL) {
                if (node->op != LISTEND) {
                    printf("!!!\n");
                    return NULL;
                }
            }
            lh = ast_eval_expr(node->content.children.lhs);
            rh = ast_eval_expr(node->content.children.rhs);
    }
    switch(node->op) {
        /* These operations act on the left/right nodes of the tree. */
        /* MATH */
        case ADD:
            to_ret = vars_sum(lh, rh);
            break;
        case SUB:
            to_ret = vars_diff(lh, rh);
            break;
        case MUL:
            to_ret = vars_product(lh, rh);
            break;
        case DIV:
            to_ret = vars_quotient(lh, rh);
            break;
        case CONCAT:
            to_ret = vars_concat(lh, rh);
            break;
        /* VARS */
        case CREATE:
            new = addvar(getvar_str_fv(lh));
            if (rh != NULL) {
                var_assign_fv(new, rh);
            }
            break;
        case ASSIGN:
            new = find_var(getvar_str_fv(lh));
            if (new == NULL) {
                printf("--!-- %s: no such variable\n", getvar_str_fv(lh));
            } else {
                var_assign_fv(find_var(getvar_str_fv(lh)), rh);
            }
            break;
        case PRINT:
            if (debug) printf("-- output: ");
            printf("%s", getvar_str_fv(lh));
            if (debug) printf(" --\n");
            break;
        case VARNAME:
            to_ret = find_var(getvar_str_fv(lh));
            if (to_ret == NULL) {
                printf("--!-- %s: no such variable\n", getvar_str_fv(lh));
                to_ret = newvar_int(0);
            }
            break;
        case FUNCCALL:
            /* LH of FUNCCALL is the function to call; RH is the arguments. */
            to_ret = call_func(getvar_function_fv(lh), rh->content.l);
            break;
        case ELEMENT:
            to_ret = element_at(getvar_list_fv(lh), getvar_int_fv(rh));
            break;
        case LISTELEM:
            if (debug) printf("A list element.\n");
            /* listelem's LHS = element to append,
               RHS = list to append to */
            list_push(rh->content.l, lh);
            to_ret = rh;
            break;
        case LISTEND:
            if (debug) printf("The end of the list.\n");
            /* the LHS is the last item in a list, so
               create an empty list and put the item in it */
            to_ret = newvar_empty_list();
            if (to_ret->content.l == NULL) {
                printf("Out of memory; cannot allocate space for a new list!\n");
                break;
            }
            if (lh != NULL) {
                list_push(to_ret->content.l, lh);
            }
            break;
        case EXPR:
            if (current_scope->last_val != NULL) {
                free_var(current_scope->last_val);
            }
            current_scope->last_val = malloc(sizeof(var));
            var_copy(current_scope->last_val, lh);
            break;
        case EVAL:
            new_scope();
            to_ret = eval_string(lh->content.s);
            pop_scope();
            break;
        /* COMPARISONS */
        /* ... are handled by a different function because they're tedious and long */
        case NUM_GT:
        case NUM_LT:
        case NUM_GTEQ:
        case NUM_LTEQ:
        case NUM_EQ:
        case NUM_NE:
        case STR_GT:
        case STR_LT:
        case STR_GTEQ:
        case STR_LTEQ:
        case STR_EQ:
        case STR_NE:
            to_ret = vars_cmp(lh, rh, node->op);
            break;
        default:
            printf("-!!!- AST operation %c (%d) unimplemented\n", node->op, node->op);
    }
    if (lh)
    if (!lh->bound) free_var(lh);
    if (rh)
    if (rh != NULL) {
        if (to_ret != rh) {
            if (!rh->bound) free_var(rh);
        }
    }
    return to_ret;
}

ast_node *real_node(enum asttypes type, ast_node *lhs, ast_node *rhs, int line_num) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = type;
    to_return->content.children.lhs = lhs;
    to_return->content.children.rhs = rhs;
    to_return->line_num = line_num;
    to_return->flags = 0;
    return to_return;
}

ast_node *node_int(int val, int line_num) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = TERMINT;
    to_return->content.termint = val;
    to_return->line_num = line_num;
    to_return->flags = 0;
    return to_return;
}

ast_node *node_dbl(double val, int line_num) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = TERMDBL;
    to_return->content.termdbl = val;
    to_return->line_num = line_num;
    to_return->flags = 0;
    return to_return;
}

ast_node *node_str(char *val, int line_num) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = TERMSTR;
    to_return->content.termstr = val;
    to_return->line_num = line_num;
    to_return->flags = 0;
    return to_return;
}

ast_node *node_name(char *val, int line_num) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = TERMNAME;
    to_return->content.termstr = val;
    to_return->line_num = line_num;
    to_return->flags = 0;
    return to_return;
}

ast_node *node_boolean(int val, int line_num) {
    ast_node *to_return = malloc(sizeof(ast_node));
    if (to_return == NULL) {
        printf("Possibly out of memory!\n");
        return NULL;
    }
    to_return->op = TERMBOOLEAN;
    to_return->content.termint = val;
    to_return->line_num = line_num;
    to_return->flags = 0;
    return to_return;
}

ast_node *node_nothing(int line_num) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = EMPTY;
    to_return->line_num = line_num;
    to_return->flags = 0;
    return to_return;
}

void free_node(ast_node *node) {
    if (node == NULL) {
        if (debug) printf("But it is null.\n");
        return;
    }
    if (debug) printf("Freeing node. Op: %c\n", node->op);
    if (node->op == TERMSTR || node->op == TERMNAME) {
        if (node->content.termstr != NULL) {
            free(node->content.termstr);
            node->content.termstr = NULL;
        } else {
            if (debug) printf("We already freed its string component.\n");
        }
    } else if (node->op != TERMINT && node->op != TERMDBL
            && node->op != TERMBOOLEAN
            && node->op != EMPTY) {
        if (debug) printf("Freeing LHS of %c...\n", node->op);
        free_node(node->content.children.lhs);
        node->content.children.lhs = NULL;
        if (node->content.children.rhs != NULL) {
            if (debug) printf("Freeing RHS of %c...\n", node->op);
            free_node(node->content.children.rhs);
            node->content.children.rhs = NULL;
        }
    }
    if (debug) printf("Freeing node %c.\n", node->op);
    free(node);
}

void free_var(var *to_free) {
    if (to_free != NULL) {
        clear_var_ptrs(to_free);
        if (to_free->str_equiv != NULL) {
            free(to_free->str_equiv);
        }
        free(to_free);
    }
}

void clear_var_ptrs(var *to_free) {
    if (to_free->type == STRING) {
        free(to_free->content.s);
    }
    if (to_free->type == LIST) {
        free_list(to_free->content.l);
    }
    if (to_free->type == FUNCTION) {
        free_func(to_free->content.f);
    }
}

void unbind(binding *to_free) {
    if (to_free != NULL) {
        if (to_free->var) {
            free_var(to_free->var);
            to_free->var = NULL;
        }
        free(to_free);
    }
}

void cleanup() {
    binding *to_del, *tmp;
    HASH_ITER(hh, current_scope->vars, to_del, tmp) {
        HASH_DEL(current_scope->vars, to_del);
        unbind(to_del);
    }
    //free_node(root);
    free(current_scope);
}

var *newvar_int(int val) {
    var *t = alloc_var();
    if (t != NULL) {
        t->type = INT;
        t->content.i = val;
        t->bound = 0;
        t->str_equiv = NULL;
    }
    return t;
}

var *newvar_dbl(double val) {
    var *t = alloc_var();
    if (t != NULL) {
        t->type = DOUBLE;
        t->content.d = val;
        t->bound = 0;
        t->str_equiv = NULL;
    }
    return t;
}

var *newvar_str(char *str) {
    var *t = alloc_var();
    if (t != NULL) {
        t->type = STRING;
        t->content.s = (char*)malloc(strlen(str)+1);
        strcpy(t->content.s, str);
        t->bound = 0;
        t->str_equiv = NULL;
    }
    return t;
}

var *newvar_boolean(int val) {
    var *t = alloc_var();
    if (t != NULL) {
        t->type = BOOLEAN;
        if (val) t->content.i = 1;
        else t->content.i = 0;
        t->bound = 0;
        t->str_equiv = NULL;
    }
    return t;
}

var *newvar_nothing() {
    var *t = alloc_var();
    if (t != NULL) {
        t->type = NOTHING;
        t->bound = 0;
        t->str_equiv = NULL;
    }
    return t;
}

ast_node *ast_copy(ast_node *node) {
    if (node == NULL) return NULL;
    if (debug) printf("Copy AST node: %c (%d)\n", node->op, node->op);
    ast_node *new_node = malloc(sizeof(ast_node));
    *new_node = *node;
    if (node->op == TERMSTR) {
        char *new_str = malloc((strlen(node->content.termstr)+1)*sizeof(char));
        strcpy(new_str, node->content.termstr);
        new_node->content.termstr = new_str;
    } else if (node->op != TERMBOOLEAN
            && node->op != TERMDBL
            && node->op != TERMNAME
            && node->op != TERMINT
            && node->op != EMPTY) {
        new_node->content.children.lhs = ast_copy(node->content.children.lhs);
        new_node->content.children.rhs = ast_copy(node->content.children.rhs);
    }
    if (debug) printf("Done with %c (%d).\n", node->op, node->op);
    return new_node;
}

var *newvar_func(list *param_names, ast_node *exec, enum flags flags) {
    list *l = alloc_list_size(param_names->size);
    list_copy(l, param_names);
    /* now copy the AST nodes */
    ast_node *new_node = ast_copy(exec);
    var *v = alloc_var();
    if (v != NULL) {
        v->type = FUNCTION;
        v->content.f = malloc(sizeof(function));
        if (v->content.f == NULL) {
            printf("Out of memory; cannot create new function!\n");
            return NULL;
        }
        v->content.f->parameters = l;
        v->content.f->exec = new_node;
        v->content.f->flags = flags;
        v->bound = 0;
        v->str_equiv = NULL;
    }
    return v;
}

var *newvar_empty_list() {
    var *t = alloc_var();
    if (t != NULL) {
        t->type = LIST;
        t->content.l = alloc_list();
        if (t->content.l == NULL)
            printf("Out of memory -- cannot create new list!\n");
        t->bound = 0;
        t->str_equiv = NULL;
    }
    return t;
}

var *newvar_list(list *val) {
    var *t = alloc_var();
    if (t != NULL) {
        t->type = LIST;
        t->content.l = alloc_list_size(val->max_size);
        if (t->content.l == NULL)
            printf("Out of memory -- cannot create new list!\n");
        list_copy(t->content.l, val);
        t->bound = 0;
        t->str_equiv = NULL;
    }
    return t;
}

var *alloc_var() {
    var *t = (var*)malloc(sizeof(var));
    if (t == NULL) {
        printf("Out of memory!\n");
    }
    t->type = UNDEFINED;
    return t;
}

var *vars_sum(var *v1, var *v2) {
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.d+v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl(v1->content.d+v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl(v1->content.d+atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.i+v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(v1->content.i+v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(v1->content.i+atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(atoi(v1->content.s)+v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(atoi(v1->content.s)+v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(atoi(v1->content.s)+atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else {
        return newvar_int(0);
    }
}

var *vars_diff(var *v1, var *v2) {
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.d-v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl(v1->content.d-v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl(v1->content.d-atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.i-v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(v1->content.i-v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(v1->content.i-atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(atoi(v1->content.s)-v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(atoi(v1->content.s)-v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(atoi(v1->content.s)-atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else {
        return newvar_int(0);
    }
}

var *vars_product(var *v1, var *v2) {
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.d*v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl(v1->content.d*v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl(v1->content.d*atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.i*v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(v1->content.i*v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(v1->content.i*atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(atoi(v1->content.s)*v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(atoi(v1->content.s)*v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(atoi(v1->content.s)*atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else {
        return newvar_int(0);
    }
}

var *vars_quotient(var *v1, var *v2) {
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.d/v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl(v1->content.d/v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl(v1->content.d/atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            return newvar_dbl((double)v1->content.i/v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl((double)v1->content.i/v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl((double)v1->content.i/atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            return newvar_dbl((double)atoi(v1->content.s)/v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl((double)atoi(v1->content.s)/v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl((double)atoi(v1->content.s)/atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else {
        return newvar_int(0);
    }
}

var *vars_concat(var *v1, var *v2) {
    int len1, len2;
    char *strtoret;
    var *vartoret;
    if (v1->type == STRING) len1 = strlen(getvar_str_fv(v1));
    else len1 = 16;
    if (v2->type == STRING) len2 = strlen(getvar_str_fv(v2));
    else len2 = 16;
    strtoret = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            sprintf(strtoret, "%g%g", v1->content.d, v2->content.d);
        } else if (v2->type == INT) {
            sprintf(strtoret, "%g%d", v1->content.d, v2->content.i);
        } else if (v2->type == STRING) {
            sprintf(strtoret, "%g%s", v1->content.d, v2->content.s);
        } else {
            sprintf(strtoret, "%g", v1->content.d);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            sprintf(strtoret, "%d%g", v1->content.i, v2->content.d);
        } else if (v2->type == INT) {
            sprintf(strtoret, "%d%d", v1->content.i, v2->content.i);
        } else if (v2->type == STRING) {
            sprintf(strtoret, "%d%s", v1->content.i, v2->content.s);
        } else {
            sprintf(strtoret, "%d", v1->content.i);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            sprintf(strtoret, "%s%g", v1->content.s, v2->content.d);
        } else if (v2->type == INT) {
            sprintf(strtoret, "%s%d", v1->content.s, v2->content.i);
        } else if (v2->type == STRING) {
            sprintf(strtoret, "%s%s", v1->content.s, v2->content.s);
        } else {
            sprintf(strtoret, "%s", v1->content.s);
        }
    } else {
        if (v2->type == DOUBLE) {
            sprintf(strtoret, "%g", v2->content.d);
        } else if (v2->type == INT) {
            sprintf(strtoret, "%d", v2->content.i);
        } else if (v2->type == STRING) {
            sprintf(strtoret, "%s", v2->content.s);
        } else {
            free(strtoret);
            return newvar_str("");
        }
    }
    /* because newvar_str strcpy's its argument */
    vartoret = newvar_str(strtoret);
    free(strtoret);
    return vartoret;
}

var *vars_cmp(var *v1, var *v2, enum asttypes type) {
    switch (type) {
        case NUM_EQ:
            return newvar_boolean(getvar_double_fv(v1) == getvar_double_fv(v2));
        case NUM_NE:
            return newvar_boolean(getvar_double_fv(v1) != getvar_double_fv(v2));
        case NUM_GT:
            return newvar_boolean(getvar_double_fv(v1) > getvar_double_fv(v2));
        case NUM_LT:
            return newvar_boolean(getvar_double_fv(v1) < getvar_double_fv(v2));
        case NUM_GTEQ:
            return newvar_boolean(getvar_double_fv(v1) >= getvar_double_fv(v2));
        case NUM_LTEQ:
            return newvar_boolean(getvar_double_fv(v1) <= getvar_double_fv(v2));
        case STR_EQ:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) == 0);
        case STR_NE:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) != 0);
        case STR_GT:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) > 0);
        case STR_LT:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) < 0);
        case STR_GTEQ:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) >= 0);
        case STR_LTEQ:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) <= 0);
        default:
            printf("I don't know how to compare by %c.\n", type);
            return NULL;
    }
}

void bind(char *name, var *value) {
    var *new_var = addvar(name);
    var_copy(new_var, value);
}

var *var_assign_fv(var *find, var *value) {
    if (value != NULL) {
        switch (value->type) {
            case STRING:
                setvar_str_fv(find, getvar_str_fv(value));
                break;
            case INT:
                setvar_int_fv(find, getvar_int_fv(value));
                break;
            case DOUBLE:
                setvar_double_fv(find, getvar_double_fv(value));
                break;
            case BOOLEAN:
                setvar_boolean_fv(find, getvar_boolean_fv(value));
                break;
            case LIST:
                setvar_list_fv(find, getvar_list_fv(value));
                break;
            case FUNCTION:
                setvar_function_fv(find, getvar_function_fv(value));
                break;
            case NOTHING:
                make_var_nothing(find);
                break;
            default:
                setvar_int_fv(find, getvar_int_fv(value));
        }
    } else {
        if (debug)printf("...something went wrong\n");
        setvar_int_fv(find, 0);
    }
    return find;
}

char *str_dup(char *str) {
    char *to_ret = malloc ((strlen(str)+1) * sizeof(char));
    if (to_ret == NULL) return to_ret;
    strcpy(to_ret, str);
    return to_ret;
}

/* Replaces characters with backslashes in front (\n, \t, \\, etc.)
   with their actual escape sequence equivalent (newline, tab, \, etc.) */
char *escape_chars(char *str) {
    /* this might waste a bit of space, but we know the new string will always
       be at most as long as the old */
    char *new = calloc(strlen(str)+1, sizeof(char));
    if (new != NULL) {
        int oldIndex = 0;
        int newIndex = 0;
        char last = 0;
        for (oldIndex = 0; str[oldIndex]; oldIndex++) {
            if (last != '\\') {
                if (str[oldIndex] != '\\') {
                    new[newIndex] = str[oldIndex];
                    newIndex++;
                }
            } else {
                switch (str[oldIndex]) {
                    case 'n':
                        new[newIndex] = '\n'; break;
                    case 'r':
                        new[newIndex] = '\r'; break;
                    case 't':
                        new[newIndex] = '\t'; break;
                    case 'b':
                        new[newIndex] = '\b'; break;
                    case 'a':
                        new[newIndex] = '\a'; break;
                    case 'f':
                        new[newIndex] = '\f'; break;
                    case 'v':
                        new[newIndex] = '\v'; break;
                    case '\'':
                        new[newIndex] = '\''; break;
                    case '"':
                        new[newIndex] = '"'; break;
                    case '\\':
                        new[newIndex] = '\\'; break;
                    default:
                        fprintf(stderr,
                            "Unrecognized escape sequence \\%c, interpreting as literal character\n",
                            str[oldIndex]);
                        new[newIndex] = str[oldIndex];
                }
                newIndex++;
            }
            last = str[oldIndex];
        }
    }
    free(str);
    return new;
}

void new_scope() {
    scope *new_scope = malloc(sizeof(scope));
    new_scope->outer = current_scope;
    new_scope->vars = NULL;
    new_scope->last_val = NULL;
    current_scope = new_scope;
}

void pop_scope() {
    scope *next = current_scope->outer;
    binding *to_del, *tmp;
    /* clear out all the variables */
    HASH_ITER(hh, current_scope->vars, to_del, tmp) {
        HASH_DEL(current_scope->vars, to_del);
        unbind(to_del);
    }
    if (current_scope->last_val) {
        free_var(current_scope->last_val);
    }
    if (current_scope) {
        free(current_scope);
    }
    current_scope = next;
}
