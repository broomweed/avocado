#include "apothecary.h"

/* Allocates a new variable. */
var *var_new() {
    var *made = malloc(sizeof(var));
    made->props = NULL;
    made->refs = 0;
    made->class = Undefined;
}

/* Sets a variable to an integer value and changes
 * its class properly. */
void var_set_int(var *to_set, int i) {
    to_set->ct.i = i;
    to_set->class = Integer;
}

/* Sets a variable to a function value and changes
 * its class properly. */
void var_set_func(var *to_set, function *f) {
    to_set->ct.f = f;
    to_set->class = Function;
}

/* Sets a variable to a string value and changes its
 * class properly. */
void var_set_str(var *to_set, char *str) {
    to_set->ct.s = malloc((strlen(str)+1)*sizeof(char));
    strcpy(to_set->ct.s, str);
    to_set->class = String;
}

/* Sets a variable to a list value and changes its
 * class properly. */
void var_set_list(var *to_set, list *l) {
    to_set->ct.l = l;
    to_set->class = List;
}

/* Calls a method on a variable. First it looks in the
 * variable's local property list, then it looks through
 * its class hierarchy. If it finds something callable,
 * it calls it. If not, error. */
var *var_call_method(var *v, char *name, list *params) {
    binding *prop;
    var *method = var_get_prop(v, name);
    HASH_FIND_STR(v->props, name, prop);
    if (prop) {
        method = prop->v;
    } else {
        method = class_find_item(v->class, name);
    }
    if (method == NULL) {
        gen_error("item of class '%s' has no method '%s'\n", v->class->name, name);
    }
    var *result;
    if (method->class == Function) {
        /* If it's a function we already know it's callable,
         * so there's no need to extract all the extra _call
         * method stuff in order to call it. This has the
         * effect that you can't override Function::_call,
         * but if you want to do that you should make a subclass
         * anyway rather than changing behavior for all functions
         * everywhere. */
        result = func_call(method->ct.f, v, params);
    } else {
        /* If it's not a function but rather some other class
         * (let's call it X) we check if it's callable and
         * call X::_call(v, params).
         * Note that X::_call must be a bona fide Function,
         * not just anything that can be called, in order
         * to stop things getting too out of hand. */
        var *callfunc = var_get_prop(method, "_call");
        if (!callfunc || callfunc->class != Function) {
            gen_error("item '%s::%s' is of class '%s'; is not callable.\n",
                    v->class->name, name, method->class->name);
        }
        /* Lists are a pain and kind of inefficient allocation-wise,
         * hence the optimization for Functions above. */
        list *meta_params = list_new();
        list_push(meta_params, v);
        var *param_var = var_new();
        var_set_list(param_var, params);
        list_push(meta_params, param_var);
        result = func_call(callfunc->ct.f, method, meta_params);
        list_free(meta_params);
        var_free(param_var);
    }
    return result;
}

/* Gets a property of a variable, either from its local
 * hash table or from its class definition. */
var *var_get_prop(var *v, char *name) {
    binding *prop;
    HASH_FIND_STR(v->props, name, prop);
    if (prop) {
        return prop->v;
    } else {
        var *result = class_find_item(v->class, name);
        if (result) {
            return result;
        } else {
            return NULL;
        }
    }
}

/* Prints out a variable's type and stringification. It
 * does this by calling its `__to_str` method. If nothing else,
 * this defaults to Obj::__to_str which just prints <Class 0xptr>. */
void var_dump(var *v) {
    printf("%-16s", v->class->name);
    var *str = var_call_method(v, "__to_str", NULL);
    printf("%s\n", str->ct.s);
    var_check_refs(str);
}

/* This removes a reference-count from a variable and checks
 * whether it should go away. It's called when lists are freed,
 * for example. */
void var_unref(var *v) {
    v->refs--;
    var_check_refs(v);
}

/* This checks a variable's reference count. If it's at zero,
 * it frees the variable. */
void var_check_refs(var *v) {
    if (!v->refs) {
        var_free(v);
    }
}

/* This frees a variable and its associated pointers. This function
 * should probably not be called directly, unless you really know
 * what you're doing. */
void var_free(var *v) {
    if (v->class == String) {
        free(v->ct.s);
    }
    if (v->class == Function) {
        free(v->ct.f);
    }
    if (v->class == List) {
        list_free(v->ct.l);
    }
    if (v->class == Class) {
        class_free(v->ct.c);
    }
    binding *to_free, *temp;
    HASH_ITER(hh, v->props, to_free, temp) {
        var_unref(to_free->v);
        HASH_DEL(v->props, to_free);
        free(to_free);
    }
    free(v);
}
