#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"
#include "avocado.h"

extern scope *outermost;
extern scope *current_scope;

/* var-setting by name */
void setvar_str(char *name, char *val);
void setvar_double(char *name, double val);
void setvar_int(char *name, int val);
void setvar_boolean(char *name, int val);
/* var-setting by pointer */
void setvar_str_fv(var *var, char *val);
void setvar_double_fv(var *var, double val);
void setvar_int_fv(var *var, int val);
void setvar_boolean_fv(var *var, int val);
/* var-getting by name */
int getvar_int(char *name);
char *getvar_str(char *name);
double getvar_double(char *name);
int getvar_boolean(char *name);
/* var-getting by pointer */
int getvar_int_fv(var *var);
char *getvar_str_fv(var *var);
double getvar_double_fv(var *var);
int getvar_boolean_fv(var *var);
/* var stuff */
var *addvar(char *name);
var *find_var(char *name);
/* ast stuff */
var *ast_eval_expr(ast_node *node);
ast_node *node(enum asttypes type, ast_node *lhs, ast_node *rhs);
ast_node *node_int(int val);
ast_node *node_str(char *val);
ast_node *node_dbl(double val);
ast_node *node_name(char *val);
ast_node *node_boolean(int val);
ast_node *node_nothing();
/* mem stuff */
void free_node(ast_node *node);
var *alloc_var();
void free_var(var *to_free);
void unbind(binding *to_free);
void cleanup();

/* new-var code */
var *newvar_int(int val);
var *newvar_str(char *str);
var *newvar_dbl(double val);
var *newvar_boolean(int val);
var *newvar_nothing();
var *var_assign(char *name, var *value);
var *var_assign_fv(var *new, var *value);

/* var arithmetic/operators */
var *vars_sum(var *v1, var *v2);
var *vars_diff(var *v1, var *v2);
var *vars_product(var *v1, var *v2);
var *vars_quotient(var *v1, var *v2);
var *vars_concat(var *v1, var *v2);
var *vars_cmp(var *v1, var *v2, enum asttypes type);

char *str_dup(char *str);

void setvar_str(char *name, char *val) {
    var *to_set = find_var(name);
    if (to_set == NULL) {
        to_set = addvar(name);
    }
    if (to_set->type == STRING) {
        free(to_set->content.s);
    }
    to_set->content.s = (char*)malloc(strlen(val)*sizeof(char));
    strcpy(to_set->content.s, val);
    to_set->type = STRING;
}

void setvar_double(char *name, double val) {
    var *to_set = find_var(name);
    if (to_set == NULL) {
        to_set = addvar(name);
    }
    if (to_set->type == STRING) {
        free(to_set->content.s);
    }
    to_set->content.d = val;
    to_set->type = DOUBLE;
}

void setvar_int(char *name, int val) {
    var *to_set = find_var(name);
    if (to_set == NULL) {
        to_set = addvar(name);
    }
    if (to_set->type == STRING) {
        free(to_set->content.s);
    }
    to_set->content.i = val;
    to_set->type = INT;
}

void setvar_boolean(char *name, int val) {
    var *to_set = find_var(name);
    setvar_boolean_fv(to_set, val);
}

void setvar_str_fv(var *to_set, char *val) {
    if (to_set->type == STRING) {
        free(to_set->content.s);
    }
    to_set->content.s = (char*)malloc((strlen(val)+1)*sizeof(char));
    strcpy(to_set->content.s, val);
    to_set->type = STRING;
}

void setvar_double_fv(var *to_set, double val) {
    if (to_set->type == STRING) {
        free(to_set->content.s);
    }
    to_set->content.d = val;
    to_set->type = DOUBLE;
}

void setvar_int_fv(var *to_set, int val) {
    if (to_set->type == STRING) {
        free(to_set->content.s);
    }
    to_set->content.i = val;
    to_set->type = INT;
}

void setvar_boolean_fv(var *to_set, int val) {
    if (to_set->type == STRING) {
        free(to_set->content.s);
    }
    if (val) to_set->content.i = 1;
    else to_set->content.i = 0;
    to_set->type = BOOLEAN;
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
    if (find == NULL) {
        addvar(name);
        setvar_str(name, "");
        return find_var(name)->content.s;
    }
    if (find->type == STRING) return find->content.s;
    if (find->type == INT) sprintf(find->str_equiv, "%d", find->content.i);
    if (find->type == DOUBLE) sprintf(find->str_equiv, "%g", find->content.d);
    return find->str_equiv;
}

double getvar_double(char *name) {
    var *find = find_var(name);
    return getvar_double_fv(find);
}

int getvar_boolean(char *name) {
    var *find = find_var(name);
    return getvar_boolean_fv(find);
}

int getvar_int_fv(var *find) {
    if (find == NULL) return 0;
    else if (find->type == INT || find->type == BOOLEAN) return find->content.i;
    else if (find->type == DOUBLE) return (int)find->content.d;
    else if (find->type == STRING) return atoi(find->content.s);
    else return 0;
}

char *getvar_str_fv(var *find) {
    char *strtoret;
    if (find == NULL) {
        return NULL;
    } else if (find->type == STRING) {
        return find->content.s;
    } else {
        strtoret = malloc(16*sizeof(char));
        if (find->type == INT) {
            sprintf(strtoret, "%d", find->content.i);
        } else if (find->type == DOUBLE) {
            sprintf(strtoret, "%g", find->content.d);
        } else if (find->type == BOOLEAN) {
            if (find->content.i)
                sprintf(strtoret, "true");
            else
                sprintf(strtoret, "false");
        }
    }
    if (find->str_equiv) {
        free(find->str_equiv);
    }
    find->str_equiv = strtoret;
    return strtoret;
}

double getvar_double_fv(var *find) {
    if (find == NULL) return 0.0f;
    else if (find->type == STRING) return atof(find->content.s);
    else if (find->type == INT || find->type == BOOLEAN) return (double)find->content.i;
    else if (find->type == DOUBLE) return find->content.d;
    else return 0.0f;
}

int getvar_boolean_fv(var *find) {
    if (find == NULL) return 0;
    else if (find->type == NOTHING) return 0;
    else if (find->type == BOOLEAN && find->content.i == 0) return 0;
    else if (find->type == INT && find->content.i == 0) return 0;
    else if (find->type == DOUBLE && find->content.d == 0) return 0;
    else return 1;
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
    var *lh, *rh, *to_ret, *new;
    if (node == NULL) return NULL;
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
            if (debug) printf("SCOPE END       : }}}\n");
            pop_scope();
            return lh;
        case MULTI:
            if (debug) printf("BLOCK...\n");
            ast_eval_expr(node->content.children.lhs);
            return ast_eval_expr(node->content.children.rhs);
        case IF:
            /* The control flow constructs go here because they need control over
               which/how many times to evaluate a node, rather than evaluating both
               and doing something to them. */
            if (debug) printf("If.\n");
            lh = ast_eval_expr(node->content.children.lhs);
            if (getvar_boolean_fv(lh)) {
                ast_eval_expr(node->content.children.rhs->content.children.lhs);
            } else {
                ast_eval_expr(node->content.children.rhs->content.children.rhs);
            }
            if (!lh->bound) free_var(lh);
            return NULL;
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
                printf("!!!\n");
                return NULL;
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
            printf("%s", getvar_str_fv(lh));
            break;
        case VARNAME:
            to_ret = find_var(getvar_str_fv(lh));
            if (to_ret == NULL) {
                printf("--!-- %s: no such variable\n", getvar_str_fv(lh));
                to_ret = newvar_int(0);
            }
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
            printf("AST operation `%c` unimplemented", node->op);
    }
    if (!lh->bound) free_var(lh);
    if (rh != NULL) {
        if (!rh->bound) free_var(rh);
    }
    return to_ret;
}

ast_node *node(enum asttypes type, ast_node *lhs, ast_node *rhs) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = type;
    to_return->content.children.lhs = lhs;
    to_return->content.children.rhs = rhs;
    return to_return;
}

ast_node *node_int(int val) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = TERMINT;
    to_return->content.termint = val;
    return to_return;
}

ast_node *node_dbl(double val) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = TERMDBL;
    to_return->content.termdbl = val;
    return to_return;
}

ast_node *node_str(char *val) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = TERMSTR;
    to_return->content.termstr = val;
    return to_return;
}

ast_node *node_name(char *val) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = TERMNAME;
    to_return->content.termstr = val;
    return to_return;
}

ast_node *node_boolean(int val) {
    ast_node *to_return = malloc(sizeof(ast_node));
    if (to_return == NULL) {
        printf("Possibly out of memory!\n");
        return NULL;
    }
    to_return->op = TERMBOOLEAN;
    to_return->content.termint = val;
    return to_return;
}

ast_node *node_nothing() {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = EMPTY;
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
        if (to_free->type == STRING) {
            free(to_free->content.s);
        }
        if (to_free->str_equiv != NULL) {
            free(to_free->str_equiv);
        }
        free(to_free);
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
    free_node(root);
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

var *alloc_var() {
    var *t = (var*)malloc(sizeof(var));
    if (t == NULL) {
        printf("Out of memory!\n");
    }
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

var *var_assign(char *name, var *value) {
    if (debug) printf("VAR:    %8s: ", name);
    var *find = find_var(name);
    if (find == NULL) {
        printf("--!-- %s: no such variable\n", name);
        return NULL;
    }
    if (debug) printf("%p.\n", (void*)find);
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
    if (current_scope) {
        free(current_scope);
    }
    current_scope = next;
}
