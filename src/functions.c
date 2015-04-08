#include "avocado.h"
#include <stdlib.h>

void free_func(function *func) {
    binding *to_del, *tmp;
    scope *next;
    if (debug) printf("(++ freeing params ++)\n");
    free_list(func->parameters);
    free_node(func->exec);
    /* free function's closure */
    do {
        if (debug) printf("~clear scope~\n");
        next = func->closure->outer;
        HASH_ITER(hh, func->closure->vars, to_del, tmp) {
            if (debug) printf("Clearing %s from scope. ", to_del->name);
            HASH_DEL(func->closure->vars, to_del);
            unbind(to_del);
            /*to_del->var->bound--;
            if (!to_del->var->bound) {
                free_var(to_del->var);
            }
            free(to_del);*/
        }
        /*if (func->closure->last_val) {
            unbind(func->closure->last_val);
        }*/
        if (func->closure) {
            free(func->closure);
        }
        func->closure = next;
    } while (func->closure);
    free(func);
}

function *func_copy(function *src) {
    return create_func(src->parameters, src->exec, src->flags, src->closure);
}

function *create_func_copy(list *parameters, ast_node *exec, enum flags flags, scope *closure) {
    //binding *to_increment, *tmp;
    function *dest = malloc(sizeof(function));
    dest->parameters = alloc_list_size(parameters->size);
    list_copy(dest->parameters, parameters);
    dest->exec = ast_copy(exec);
    dest->flags = flags;
    dest->closure = scope_copy(closure);
    return dest;
}

function *create_func(list *parameters, ast_node *exec, enum flags flags, scope *closure) {
    //binding *old_binding, *tmp;
    function *dest = malloc(sizeof(function));
    dest->parameters = alloc_list_size(parameters->size);
    list_copy(dest->parameters, parameters);
    dest->exec = ast_copy(exec);
    dest->flags = flags;
    //dest->closure = closure;
    dest->closure = copy_closure(closure);
    return dest;
}

scope *copy_closure(scope *closure) {
    binding *old_binding, *tmp;
    scope *to_ret = malloc(sizeof(scope));
    to_ret->last_val = NULL;
    to_ret->is_eval = closure->is_eval;
    to_ret->vars = NULL;
    HASH_ITER(hh, closure->vars, old_binding, tmp) {
        binding *new_binding = malloc(sizeof(binding));
        strncpy(new_binding->name, old_binding->name, 64);
        bind(new_binding, old_binding->var);
        HASH_ADD_STR(to_ret->vars, name, new_binding);
    }
    if (closure->outer) {
        to_ret->outer = copy_closure(closure->outer);
    } else {
        to_ret->outer = NULL;
    }
    return to_ret;
}

var *call_func(function *func, list *parameters) {
    var *argval, *argname, *retval;

    if (func == NULL) {
        fprintf(stderr, "Uh-oh, we're goin' down!\n");
    }

    switch_to_func_scope(func->closure);
    new_scope();

    //list *param_names = alloc_list_size(func->parameters->size);
    //list_copy(param_names, func->parameters);

    list *param_names = func->parameters;

    /* bind_name parameters in scope */
    for (int i = 0; i < param_names->size; i++) {
        argname = element_at(param_names, i);
        argval = list_shift(parameters);
        if (argval == NULL) {
            error("Not enough arguments to function");
            return_func_scope();
            free_list(parameters);
            return newvar_undefined();
        }
        if (debug) printf("Binding %s @ %p as %s (%d)\n", getvar_str_fv(argval),
                (void*)argval, getvar_str_fv(argname), argval->type);
        bind_name(getvar_str_fv(argname), argval);
    }

    /*while ((argval = list_shift(parameters))) {
        argname = list_shift(param_names);
        if (argname == NULL) {
            error("Too many arguments to function");
            return_func_scope();
            free_list(param_names);
            free_list(parameters);
            return newvar_nothing();
        }
        if (debug) printf("Binding %s as %s (%d)\n", getvar_str_fv(argval), getvar_str_fv(argname), argval->type);
        bind_name(getvar_str_fv(argname), argval);
        //unreference(argval);
        free_var(argname);
    }*/
    //free_list(parameters);

    if (parameters->size > 0) {
        error("Too many arguments to function");
        return_func_scope();
        //free_list(param_names);
        return newvar_nothing();
    }

    if (debug) printf("Pre-exec.\n");

    /* the most important line */
    ast_eval_expr(func->exec);

    if (debug) printf("post-exec\n");

    if (current_scope->last_val == NULL) {
        retval = newvar_undefined();
        retval->bound++;
    } else {
        retval = current_scope->last_val->var;
        if (debug) printf("Binding retval @ %p: %d -> ", (void*)retval, retval->bound);
        retval->bound++;
        if (debug) printf("%d\n", retval->bound);
    }
    if (debug) printf("-- RETURN VALUE: %s -- [%p]\n", getvar_str_fv(retval), (void*)retval);

    pop_scope();

    unbind(current_scope->last_val);

    return_func_scope();

    //free_list(param_names);
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
