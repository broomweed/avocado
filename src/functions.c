#include "avocado.h"
#include <stdlib.h>

void free_func(function *func) {
    free_list(func->parameters);
    free_node(func->exec);
    free(func);
}

function *func_copy(function *src) {
    return create_func(src->parameters, src->exec);
}

function *create_func(list *parameters, ast_node *exec) {
    function *dest = malloc(sizeof(function));
    dest->parameters = alloc_list_size(parameters->size);
    list_copy(dest->parameters, parameters);
    dest->exec = ast_copy(exec);
    return dest;
}

var *call_func(function *func, list *parameters) {
    var *arg, *argname;
    list *param_names = alloc_list_size(func->parameters->size);
    list_copy(param_names, func->parameters);
    new_scope();
    /* bind parameters in scope */
    while ((arg = list_shift(parameters))) {
        argname = list_shift(param_names);
        if (argname == NULL) {
            error("Too many arguments to function");
            return NULL;
        }
        if (debug) printf("Binding %s as %s (%d)", getvar_str_fv(arg), getvar_str_fv(argname), arg->type);
        bind(getvar_str_fv(argname), arg);
        free_var(arg);
        free_var(argname);
    }
    if (param_names->size > 0) {
        error("Not enough arguments to function");
        return NULL;
    }
    ast_eval_expr(func->exec);
    pop_scope();
    free_list(param_names);
    return NULL;
}
