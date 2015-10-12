#include "apothecary.h"

list *list_new() {
    list *made = malloc(sizeof(list));
    made->size = 0;
    made->max_size = 1;
    made->head = (var**)malloc(made->max_size * sizeof(*made->head));
    return made;
}

void list_push (list *l, var *v) {
    var **tmp;
    if (l->size >= l->max_size) {
        l->max_size <<= 1;
        tmp = realloc(l->head, l->max_size * sizeof(*l->head));
        if (tmp == NULL) {
            gen_error("Unable to reallocate memory for list");
            return;
        }
        l->head = tmp;
    }
    l->head[l->size] = v;
    v->refs++;
    l->size++;
}

void list_dump (list *l) {
    printf("type\t\tvalue\n---------------------\n");
    for (int i = 0; i < l->size; i++) {
        var_dump(l->head[i]);
    }
}

var *list_get(list *l, int index) {
    return l->head[index];
}

void list_free(list *l) {
    for (int i = 0; i < l->size; i++) {
        var_unref(list_get(l, i));
    }
    free(l->head);
    free(l);
}
