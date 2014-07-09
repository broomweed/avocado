#include "avocado.h"
#include <stdlib.h>

void free_func(function *func) {
    free_list(func->parameters);
    free_node(func->exec);
    free(func);
}

function *func_copy(function *src) {
    return create_func(src->parameters, src->exec, src->flags);
}

function *create_func(list *parameters, ast_node *exec, enum flags flags) {
    function *dest = malloc(sizeof(function));
    dest->parameters = alloc_list_size(parameters->size);
    list_copy(dest->parameters, parameters);
    dest->exec = ast_copy(exec);
    dest->flags = flags;
    return dest;
}

var *call_func(function *func, list *parameters) {
    var *arg, *argname, *retval;
    if (func == NULL) {
        printf("Uh-oh! We're goin' down!\n");
    }
    list *param_names = alloc_list_size(func->parameters->size);
    list_copy(param_names, func->parameters);
    printf("GLAGS: %d\n", func->flags);
    if (!(func->flags & FUNC_BLOCK)) {
        new_scope();
    }
    /* bind parameters in scope */
    while ((arg = list_shift(parameters))) {
        argname = list_shift(param_names);
        if (argname == NULL) {
            error("Too many arguments to function");
            return NULL;
        }
        if (debug) printf("Binding %s as %s (%d)\n", getvar_str_fv(arg), getvar_str_fv(argname), arg->type);
        bind(getvar_str_fv(argname), arg);
        free_var(arg);
        free_var(argname);
    }
    if (param_names->size > 0) {
        error("Not enough arguments to function");
        return NULL;
    }
    ast_eval_expr(func->exec);
    if (current_scope->last_val == NULL) {
        retval = newvar_nothing();
    } else {
        retval = malloc(sizeof(var));
        var_copy(retval, current_scope->last_val);
    }
    if (debug) printf("-- RETURN VALUE: %s --\n", getvar_str_fv(retval));
    if (!(func->flags & FUNC_BLOCK)) {
        pop_scope();
    }
    free_list(param_names);
    return retval;
}

ast_node *real_node_function(int flags, ast_node *lhs, ast_node *rhs, int line_num) {
    ast_node *to_return = malloc(sizeof(ast_node));
    to_return->op = FUNCDEF;
    to_return->content.children.lhs = lhs;
    to_return->content.children.rhs = rhs;
    to_return->line_num = line_num;
    to_return->flags = flags;
    return to_return;
}
