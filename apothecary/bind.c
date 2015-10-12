#include "apothecary.h"

binding *binding_new() {
    binding *new_binding = malloc(sizeof(binding));
    new_binding->v = NULL;
    return new_binding;
}

void bind(binding *b, var *v_new) {
    if (b->v) {
        var_unref(b->v);
    }
    b->v = v_new;
    v_new->refs++;
}

void scope_bind(scope *sc, var *v, char *name) {
    binding *new_binding = malloc(sizeof(binding));
    strncpy(new_binding->name, name, 64);
    new_binding->v = NULL;
    bind(new_binding, v);
    HASH_ADD_STR(sc->vars, name, new_binding);
}

void class_bind(class *cl, var *v, char *name) {
    binding *new_binding = malloc(sizeof(binding));
    strncpy(new_binding->name, name, 64);
    new_binding->v = v;
    HASH_ADD_STR(cl->vars, name, new_binding);
}

void unbind(scope *current_scope, binding *b) {
    var_unref(b->v);
    HASH_DEL(current_scope->vars, b);
    free(b);
}

scope *scope_new(scope **current_scope_ptr) {
    scope *sc = malloc(sizeof(scope));
    sc->outer = *current_scope_ptr;
    sc->vars = NULL;
    sc->last_val = NULL;
    *current_scope_ptr = sc;
}

void scope_pop(scope **current_scope_ptr) {
    binding *to_free, *temp;
    scope *previous_scope = (*current_scope_ptr)->outer;
    HASH_ITER(hh, (*current_scope_ptr)->vars, to_free, temp) {
        unbind(*current_scope_ptr, to_free);
    }
    free(*current_scope_ptr);
    *current_scope_ptr = previous_scope;
}

var *scope_get_var(scope *scope, char *name) {
    binding *result;
    HASH_FIND_STR(scope->vars, name, result);
    return result->v;
}
