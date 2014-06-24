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
