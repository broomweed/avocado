#include "apothecary.h"

var *class_find_item(class *cl, char *name) {
    binding *found = NULL;
    class *searching;

    for (searching = cl; searching && !found; searching = searching->parent) {
        HASH_FIND_STR(searching->vars, name, found);
    }

    if (found) {
        return found->v;
    } else {
        return NULL;
    }
}

void class_add_method(class *cl, builtin_method m, char *name) {
    var *v = var_new();
    function *f = malloc(sizeof(function));
    func_set_builtin_method(f, m);
    var_set_func(v, f);
    v->refs++;
    class_bind(cl, v, name);
}

void class_set_name(class *cl, char *name) {
    strcpy(cl->name, name);
}

void class_set_parent(class *child, class *parent) {
    child->parent = parent;
}

void class_register(class *cl, scope *sc) {
    var *v = var_new();
    v->class = Class;
    v->ct.c = cl;
    scope_bind(sc, v, cl->name);
}

void class_free(class *cl) {
    binding *to_free, *temp;
    HASH_ITER(hh, cl->vars, to_free, temp) {
        HASH_DEL(cl->vars, to_free);
        var_unref(to_free->v);
        free(to_free);
    }
    free(cl);
}
