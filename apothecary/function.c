#include "apothecary.h"

var *func_call(function *f, var *self, list *params) {
    if (f->is_builtin) {
        if (f->is_method) {
            f->body.builtin_method(self, params);
        } else {
            f->body.builtin(params);
        }
    }
}

void func_set_builtin(function *f, var *(*b)(list*)) {
    f->is_builtin = 1;
    f->is_method = 0;
    f->body.builtin = b;
}

void func_set_builtin_method(function *f, var *(*b)(var*, list*)) {
    f->is_builtin = 1;
    f->is_method = 1;
    f->body.builtin_method = b;
}

void func_param_check(char *func_name, int expected, list *params) {
    if (params->size != expected) {
        gen_error("Wrong number of arguments to %s (expected %d, but got %d).", func_name, expected, params->size);
    }
}
