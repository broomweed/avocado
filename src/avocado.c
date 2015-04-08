#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"
#include "avocado.h"
#include "y.tab.h"

extern scope *outermost;
extern scope *current_scope;
extern func_scope *current_func_scope;
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
binding *find_binding(char *name);

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
binding *bind_name(char *name, var *value);
binding *bind(binding *b, var *value);
void unbind(binding *to_free);
void check_refs(var *to_unref);
void cleanup();

/* new-var code */
var *newvar_int(int val);
var *newvar_str(char *str);
var *newvar_dbl(double val);
var *newvar_boolean(int val);
var *newvar_list(list *val);
var *newvar_empty_list();
var *newvar_nothing();
var *newvar_undefined();
var *newvar_func(list *param_names, ast_node *exec, enum flags flags);
var *newvar_ref(var **ref);
var *var_assign(char *name, var *value);
var *var_assign_fv(var *new, var *value);

/* var arithmetic/operators */
var *vars_sum(var *v1, var *v2);
var *vars_diff(var *v1, var *v2);
var *vars_product(var *v1, var *v2);
var *vars_quotient(var *v1, var *v2);
var *vars_concat(var *v1, var *v2);
var *vars_cmp(var *v1, var *v2, enum asttypes type);

char *escape_chars(char *str);

/* scoping stuff */
void new_scope();
void new_eval_scope();
void pop_scope();
scope *scope_copy(scope *s);

void throw_error (const char *msg, int line_num);
void throw_warning (const char *msg, int line_num);

/* function that apparently doesn't exist in GNU library */
char *str_dup(char *str);

/* ------function definitions------ */

void throw_error (const char *msg, int line_num) {
    if (!current_scope->is_eval) {
        fprintf(stderr, "runtime error: %s near line %d\n", msg, line_num);
    } else {
        fprintf(stderr, "runtime error: %s in eval statement\n", msg);
    }
}

void throw_warning (const char *msg, int line_num) {
    if (!current_scope->is_eval) {
        fprintf(stderr, "warning: %s near line %d\n", msg, line_num);
    } else {
        fprintf(stderr, "warning: %s in eval statement\n", msg);
    }
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
            find->str_equiv = malloc((len) * sizeof(char));
            len = 0;
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
        } else if (find->type == FUNCTION) {
            sprintf(find->str_equiv, "<function>");
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
        char *str = malloc(80*sizeof(char));
        sprintf(str, "Cannot call a non-function (actual type: %d)", find->type);
        if (debug) sprintf(str + 43, " @ %p", (void*)find);
        error(str);
        free(str);
        return NULL;
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
    binding *found = find_binding(name);
    if (found == NULL) {
        return NULL;
    } else {
        return found->var;
    }
}

binding *find_binding(char *name) {
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
        return found;
    } else {
        return NULL;
    }
}

var *ast_eval_expr(ast_node *node) {
    var *lh, *rh;
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
            /* It copies the list currently (wasteful I know) so we can get rid of the
               one we had before */
            free_list(lh->content.l);
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
            var_assign_fv(lh, rh);
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
        case ASSIGN:
            /*   _______________________________________________________________
                / contains the location of the var-pointer that we're modifying \
                lh (&var) -> *lh (var)                     _________________________  _________________
                               \                          / pointer we're modifying \/ var that exists \
                                lh->content.r (&&var)  -> *lh->content.r (&var)   -> **lh->content.r (var) */
            if (debug) printf("=\n");
            lh = ast_eval_assignee(node->content.children.lhs);
            if (lh == NULL) {
                return newvar_undefined();
            }
            to_ret = ast_eval_expr(node->content.children.rhs);
            free_var(*lh->content.r);
            *lh->content.r = to_ret;
            if (debug) printf("%p: %d -> ", (void*)to_ret, to_ret->bound);
            to_ret->bound++;
            if (debug) printf("%d\n", to_ret->bound);
            if (debug) printf("--> %p = %s\n", (void*)lh, getvar_str_fv(to_ret));
            if (debug) printf("<<< %s\n", getvar_str_fv(to_ret));
            return to_ret;
        case EXPR:
            if (debug) printf("EXPR.\n");
            lh = ast_eval_expr(node->content.children.lhs);
            if (lh != NULL) {
                if (current_scope->last_val != NULL) {
                    unbind(current_scope->last_val);
                    current_scope->last_val = malloc(sizeof(binding));
                } else {
                    current_scope->last_val = malloc(sizeof(binding));
                }
                current_scope->last_val->name[0] = '\0';
                if (debug) printf("Bound LV: %d @ %p", lh->bound, (void*)lh);
                bind(current_scope->last_val, lh);
                if (debug) printf(" -> %d\n", lh->bound);
            } else {
                if (current_scope->last_val == NULL) {
                    printf("Now what in the heck is going on here.");
                }
            }
            return current_scope->last_val->var;
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
            to_ret = bind_name(getvar_str_fv(lh), newvar_undefined())->var;
            break;
        case PRINT:
            if (debug) printf("-- output: ");
            printf("%s", getvar_str_fv(lh));
            if (debug) printf(" --\n");
            to_ret = newvar_nothing();
            break;
        case VARNAME:
            to_ret = find_var(getvar_str_fv(lh));
            if (to_ret == NULL) {
                printf("--!-- %s: no such variable\n", getvar_str_fv(lh));
                to_ret = newvar_undefined();
            }
            free_var(lh);
            break;
        case FUNCCALL: ; // <-- a label can't label a declaration; a semicolon is a valid statement though.
            /* LH of FUNCCALL is the function to call; RH is the arguments. */
            function *to_call = getvar_function_fv(lh);
            if (to_call != NULL) {
                if (debug) printf("Incrementing reference count for %p (param list)\n", (void*)rh);
                to_ret = call_func(to_call, rh->content.l);
            } else {
                to_ret = newvar_undefined();
            }
            break;
        case ELEMENT:
            to_ret = element_at(getvar_list_fv(lh), getvar_int_fv(rh));
            if (to_ret == NULL) {
                error("Element index out of range");
                return newvar_undefined();
            }
            break;
        case LISTELEM:
            if (debug) printf("A list element.\n");
            /* listelem's LHS = element to append,
               RHS = list to append to */
            list_push(rh->content.l, lh);
            to_ret = rh;
            break;
        case LISTEND:
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
        case EVAL:
            new_eval_scope();
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
    check_refs(lh);
    check_refs(rh);
    return to_ret;
}

var *ast_eval_assignee(ast_node *node) {
    binding *found;
    var **to_ret;
    switch(node->op) {
        case TERMNAME:
            if (debug) printf("var name!\n");
            found = find_binding(node->content.termstr);
            if (found == NULL) {
                printf("--!-- %s: no such variable\n", node->content.termstr);
                return newvar_nothing();
            }
            to_ret = &found->var;
            break;
        case CREATE:
            if (debug) printf("lhs: create var, finding name...\n");
            var *name_var = ast_eval_expr(node->content.children.lhs);
            found = bind_name(getvar_str_fv(name_var), newvar_undefined());
            free_var(name_var);
            found->var->bound = 1;
            to_ret = &found->var;
            if (debug) printf("new var: %s (%p <- %p)!\n", found->name, (void*)found, (void*)to_ret);
            break;
        case ELEMENT:
            if (debug) printf("array element!\n");
            to_ret = ref_element_at(getvar_list_fv(ast_eval_expr(node->content.children.lhs)),
                    getvar_int_fv(ast_eval_expr(node->content.children.rhs)));
            if (to_ret == NULL) {
                error("element index out of range");
                return newvar_nothing();
            }
            break;
        default:
            if (debug) printf(":(\n");
            error("lvalue required as left operand of assignment");
            return NULL;
    }
    return newvar_ref(to_ret);
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
    //if (debug) printf("Freeing node. Op: %c\n", node->op);
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
        //if (debug) printf("Freeing LHS of %c...\n", node->op);
        free_node(node->content.children.lhs);
        node->content.children.lhs = NULL;
        if (node->content.children.rhs != NULL) {
            //if (debug) printf("Freeing RHS of %c...\n", node->op);
            free_node(node->content.children.rhs);
            node->content.children.rhs = NULL;
        }
    }
    //if (debug) printf("Freeing node %c.\n", node->op);
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
        if (to_free->var != NULL) {
            if (debug) {
                printf("Unbound %s: %d -> %d\n", to_free->name, to_free->var->bound, to_free->var->bound-1);
            }
            to_free->var->bound--;
            check_refs(to_free->var);
            //if (debug) printf("%d\n", to_free->var->bound);
            /*if (!to_free->var->bound) {
                free_var(to_free->var);
                to_free->var = NULL;
            }*/
        }
        free(to_free);
    }
}

void check_refs(var *to_unref) {
    if (debug) printf("Checking refs for var at %p: %d.", (void*)to_unref, to_unref->bound);
    if (to_unref->bound < 0) {
        error("Variable reference count decreased past zero");
        exit(1);
    }
    if (!to_unref->bound) {
        if (debug) printf("..and freeing it.\n");
        free_var(to_unref);
    } else {
        if (debug) printf("\n");
    }
}

void cleanup() {
    binding *to_del, *tmp;
        if (debug) printf("Final values of global variables:\n\
NAME\t\tPTR\t\tVALUE\n\
==========================================\n");
    HASH_ITER(hh, current_scope->vars, to_del, tmp) {
        if (debug) printf("%s\t\t%p\t%s\n", to_del->name, (void*)to_del->var, getvar_str_fv(to_del->var));
        HASH_DEL(current_scope->vars, to_del);
        unbind(to_del);
    }
    //free_node(root);
    if (debug) {
        if (current_scope->last_val) {
            printf("<last-val>\t%p\t%s\n",
                    (void*)current_scope->last_val->var, getvar_str_fv(current_scope->last_val->var));
        } else {
            printf("<last-val>\t%p\n", (void*)current_scope->last_val);
        }
    }
    unbind(current_scope->last_val);
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

var *newvar_undefined() {
    var *t = alloc_var();
    if (t != NULL) {
        t->type = UNDEFINED;
        t->bound = 0;
        t->str_equiv = NULL;
    }
    return t;
}

ast_node *ast_copy(ast_node *node) {
    if (node == NULL) return NULL;
    //if (debug) printf("Copy AST node: %c (%d)\n", node->op, node->op);
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
    //if (debug) printf("Done with %c (%d).\n", node->op, node->op);
    return new_node;
}

var *newvar_func(list *param_names, ast_node *exec, enum flags flags) {
    var *v = alloc_var();
    if (v != NULL) {
        v->type = FUNCTION;
        v->content.f = create_func(param_names, exec, flags, current_scope);
        v->bound = 0;
        v->str_equiv = NULL;
    }
    return v;
}

var *newvar_ref(var **ref) {
    var *v = alloc_var();
    if (v != NULL) {
        v->type = REFERENCE;
        v->content.r = ref;
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
    /* figure out how long the combined string should be */
    if (v1->type == STRING) len1 = strlen(getvar_str_fv(v1));
    else len1 = 16;
    if (v2->type == STRING) len2 = strlen(getvar_str_fv(v2));
    else len2 = 16;
    strtoret = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    /* sprintf them together */
    sprintf(strtoret, "%s%s", getvar_str_fv(v1), getvar_str_fv(v2));
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

binding *bind_name(char *name, var *value) {
    binding *new_binding = malloc(sizeof(binding));
    strncpy(new_binding->name, name, 64);
    new_binding->var = value;
    HASH_ADD_STR(current_scope->vars, name, new_binding);
    new_binding->var->bound++;
    if (debug) printf("bind_name %s @ %p. refcount = %d\n", name, (void*)new_binding->var, new_binding->var->bound);
    return new_binding;
}

binding *bind(binding *new_binding, var *value) {
    new_binding->var = value;
    new_binding->var->bound++;
    return new_binding;
}

var *var_assign_fv(var *find, var *value) {
    if (debug) printf("Assigning to a variable at %p...", (void*)find);
    if (value != NULL) {
        switch (value->type) {
            case STRING:
                if (debug) printf("string\n");
                setvar_str_fv(find, getvar_str_fv(value));
                break;
            case INT:
                if (debug) printf("int\n");
                setvar_int_fv(find, getvar_int_fv(value));
                break;
            case DOUBLE:
                if (debug) printf("double\n");
                setvar_double_fv(find, getvar_double_fv(value));
                break;
            case BOOLEAN:
                if (debug) printf("boolean\n");
                setvar_boolean_fv(find, getvar_boolean_fv(value));
                break;
            case LIST:
                if (debug) printf("list\n");
                setvar_list_fv(find, getvar_list_fv(value));
                break;
            case FUNCTION:
                if (debug) printf("function\n");
                setvar_function_fv(find, getvar_function_fv(value));
                break;
            case NOTHING:
                if (debug) printf("nothing\n");
                make_var_nothing(find);
                break;
            default:
                if (debug) printf("???\n");
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
                    default: ;
                        char *warning = malloc(69*sizeof(char));
                        sprintf(warning,
                            "Unrecognized escape sequence \\%c, interpreting as literal character %c",
                            str[oldIndex], str[oldIndex]);
                        warn(warning);
                        free(warning);
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
    new_scope->last_val = malloc(sizeof(binding));
    new_scope->last_val->name[0] = '\0';
    new_scope->last_val->var = NULL;
    new_scope->is_eval = 0;
    current_scope = new_scope;
    current_func_scope->top = current_scope;
}

void new_eval_scope() {
    new_scope();
    current_scope->is_eval = 1;
}

void pop_scope() {
    scope *next = current_scope->outer;
    binding *to_del, *tmp;
    /* clear out all the variables */
    HASH_ITER(hh, current_scope->vars, to_del, tmp) {
        HASH_DEL(current_scope->vars, to_del);
        unbind(to_del);
    }
    /* if there was an old last-value hanging around, get rid of it */
    if (next->last_val != NULL) {
        unbind(next->last_val);
    }
    next->last_val = malloc(sizeof(binding));
    next->last_val->name[0] = '\0';
    /* and change it to the last value of the current scope */
    current_scope->last_val->var->bound++;
    next->last_val->var = current_scope->last_val->var;
    //next->last_val->var->bound++;
    unbind(current_scope->last_val);
    if (current_scope) {
        free(current_scope);
    }
    current_scope = next;
    current_func_scope->top = current_scope;
}

void switch_to_func_scope(scope *to_switch) {
    func_scope *new_func_scope = malloc(sizeof(func_scope));
    new_func_scope->next = current_func_scope;
    new_func_scope->top = to_switch;
    current_func_scope = new_func_scope;
    current_scope = current_func_scope->top;
}

void return_func_scope() {
    func_scope *old_func_scope = current_func_scope;
    //unbind(current_func_scope->next->top->last_val);
    current_func_scope = current_func_scope->next;
    free(old_func_scope);
    current_scope = current_func_scope->top;
}

scope *scope_copy(scope *to_copy) {
    binding *item;
    scope *new;
    if (to_copy == NULL) return NULL;
    new = malloc(sizeof(scope));
    *new = *to_copy;
    new->vars = NULL;
    for (item = to_copy->vars; item != NULL; item = item->hh.next) {
        binding *new_binding = malloc(sizeof(binding));
        var *new_var = malloc(sizeof(var));
        var_copy(new_var, item->var);
        strcpy(new_binding->name, item->name);
        //new_binding->var = new_var;
        bind(new_binding, new_var);
        HASH_ADD_STR(new->vars, name, new_binding);
    }
    new->outer = scope_copy(to_copy->outer);
    return new;
}
