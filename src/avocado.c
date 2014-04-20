#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"
#include "avocado.h"

var *vars = NULL;

/* var-setting by name */
void setvar_str(char *name, char *val);
void setvar_double(char *name, double val);
void setvar_int(char *name, int val);
/* var-setting by pointer */
void setvar_str_fv(var *var, char *val);
void setvar_double_fv(var *var, double val);
void setvar_int_fv(var *var, int val);
/* var-getting by name */
int getvar_int(char *name);
char *getvar_str(char *name);
double getvar_double(char *name);
/* var-getting by pointer */
int getvar_int_fv(var *var);
char *getvar_str_fv(var *var);
double getvar_double_fv(var *var);
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
/* mem stuff */
void free_node(ast_node *node);
void free_var(var *to_free);
void cleanup();

/* new-var code */
var *newvar_int(int val);
var *newvar_str(char *str);
var *newvar_dbl(double val);
var *var_assign(char *name, var *value);

/* var arithmetic/operators */
var *vars_sum(var *v1, var *v2);
var *vars_diff(var *v1, var *v2);
var *vars_product(var *v1, var *v2);
var *vars_quotient(var *v1, var *v2);
var *vars_concat(var *v1, var *v2);

void print_var(char *str);

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

int getvar_int_fv(var *find) {
    if (find == NULL) return 0;
    if (find->type == INT) return find->content.i;
    if (find->type == DOUBLE) return (int)find->content.d;
    if (find->type == STRING) return atoi(find->content.s);
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
        }
    }
    find->str_equiv = strtoret;
    return strtoret;
}

double getvar_double_fv(var *find) {
    if (find == NULL) return 0.0f;
    if (find->type == STRING) return atof(find->content.s);
    if (find->type == INT) return (double)find->content.i;
    if (find->type == DOUBLE) return find->content.d;
    else return 0.0f;
}

var *addvar(char *name) {
    var *to_add = (var*)malloc(sizeof(var));
    if (to_add == NULL) {
        printf("Couldn't create variable %s: out of memory!\n", name);
    }
    strncpy(to_add->name, name, 64);
    to_add->type = UNDEFINED;
    to_add->str_equiv = NULL;
    HASH_ADD_STR(vars, name, to_add);
    return to_add;
}

var *find_var(char *name) {
    var *found;
    HASH_FIND_STR(vars, name, found);
    return found;
}

var *ast_eval_expr(ast_node *node) {
    var *lh, *rh, *to_ret;
    if (node == NULL) return NULL;
    if (debug) printf("Evaluating AST node: `%c`: ", node->op);
    switch(node->op) {
        /* These operations do not act directly on variables. */
        case TERMINT:
            if (debug) printf("it's an int!\n");
            return newvar_int(node->content.termint);
        case TERMSTR:
            if (debug) printf("it's a string!\n");
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
        case BLOCK:
            if (debug) printf("BLOCK...\n");
            ast_eval_expr(node->content.children.lhs);
            ast_eval_expr(node->content.children.rhs);
            return NULL;
        default:
            if (debug) printf("...\n");
            if (node->content.children.lhs == NULL) {
                printf("!!!");
                return NULL;
            }
            lh = ast_eval_expr(node->content.children.lhs);
            rh = ast_eval_expr(node->content.children.rhs);
    }
    switch(node->op) {
        /* These operations act on the left/right nodes of the tree. */
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
        case CREATE:
            addvar(getvar_str_fv(lh));
            break;
        case ASSIGN:
            var_assign(getvar_str_fv(lh), rh);
            break;
        case PRINT:
            print_var(getvar_str_fv(lh));
            break;
        default:
            printf("AST operation `%c` unimplemented", node->op);
    }
    if (lh->name[0] == '\0') free_var(lh);
    if (rh != NULL) {
        if (rh->name[0] == '\0') free_var(rh);
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

void free_node(ast_node *node) {
    if (node == NULL) return;
    if (node->op == TERMSTR || node->op == TERMNAME) {
        free(node->content.termstr);
    } else if (node->op != TERMINT && node->op != TERMDBL) {
        free_node(node->content.children.lhs);
        if (node->content.children.rhs != NULL) {
            free_node(node->content.children.rhs);
        }
    }
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

void cleanup() {
    var *to_del, *tmp;
    HASH_ITER(hh, vars, to_del, tmp) {
        HASH_DEL(vars, to_del);
        free_var(to_del);
    }
    free_node(root);
}

var *newvar_int(int val) {
    var *t = malloc(sizeof(var));
    if (t == NULL) {
        printf("Out of memory!\n");
        return NULL;
    }
    t->type = INT;
    t->content.i = val;
    t->name[0] = '\0';
    t->str_equiv = NULL;
    return t;
}

var *newvar_dbl(double val) {
    var *t = (var*)malloc(sizeof(var));
    if (t == NULL) {
        printf("Out of memory!\n");
        return NULL;
    }
    t->type = DOUBLE;
    t->content.d = val;
    t->name[0] = '\0';
    t->str_equiv = NULL;
    return t;
}

var *newvar_str(char *str) {
    var *t = (var*)malloc(sizeof(var));
    if (t == NULL) {
        printf("Out of memory!\n");
        return NULL;
    }
    t->type = STRING;
    t->content.s = (char*)malloc(strlen(str)+1);
    strcpy(t->content.s, str);
    t->name[0] = '\0';
    t->str_equiv = NULL;
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

var *var_assign(char *name, var *value) {
    if (debug) printf("Looking for variable %s...", name);
    var *find = find_var(name);
    if (find == NULL) {
        printf("--!-- %s: no such variable\n", name);
        return NULL;
    }
    if (debug) printf("It's located at %p.\n", (void*)find);
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
            default:
                setvar_int_fv(find, getvar_int_fv(value));
        }
    } else {
        if (debug)printf("...something went wrong\n");
        setvar_int_fv(find, 0);
    }
    return find;
}

void print_var(char *str) {
    int i = 0;
    char last = '\0';
    while (str[i]) {
        if (last != '\\') {
            if (str[i] != '\\') {
                putchar(str[i]);
            }
        } else {
            switch(str[i]) {
                case 'n':
                putchar('\n');
                break;
                case 't':
                putchar('\t');
                break;
                case 'r':
                putchar('\r');
                break;
                case '\'':
                putchar('\'');
                break;
                case '"':
                putchar('"');
                break;
                case '\\':
                putchar('\\');
                break;
                default:
                putchar(str[i]);
            }
        }
        last = str[i];
        i++;
    }
}
