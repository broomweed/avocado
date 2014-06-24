#include <stdlib.h>
#include "avocado.h"

extern int debug;

list *list_push (list* target, var* value);
var *list_pop(list* target);
void list_copy(list* dest, list* src);
var *element_at(list* target, int index);
int set_element(list *target, int index, var *value);
list *alloc_list();
list *alloc_list_size(int size);
void free_list(list *l);
void var_copy(var *dest, var *src);

list *list_push(list *target, var *value) {
    if (debug) printf("Push element!\n");
    if (debug) printf("target: %p; value: %p.\n", (void*)target, (void*)value);
    if (target->size+2 > target->max_size) {
        if (debug) printf("It's pretty big.\n");
        target->max_size *= 2;
        target->contents = realloc(target->contents, target->max_size * sizeof(var));
        if (target->contents == NULL) {
            return NULL;
        }
    }
    var_copy(&target->contents[target->size + target->min_index], value);
    target->contents[target->size].bound = 1;
    target->size++;
    if (debug) printf("The new element is located at %p.\n",
            (void*)element_at(target, target->size-1));
    if (debug) {
        printf("List now: ");
        for (int i = target->min_index; i < target->size + target->min_index; i++) {
            printf("%s ", getvar_str_fv(element_at(target, i)));
        }
        printf("\n");
    }
    return target;
}

var *list_pop(list *target) {
    var *to_ret = malloc(sizeof(var));
    var_copy(to_ret, element_at(target, target->size-1));
    if (target->size <= target->max_size/2) {
        target->max_size /= 2;
        target->contents = realloc(target->contents, target->max_size * sizeof(var));
        if (target->contents == NULL) {
            return NULL;
        }
    }
    target->size--;
    return to_ret;
}

var *list_shift(list *target) {
    if (debug) printf("Shift list.\n");
    if (target->size > 0) {
        var *to_ret = malloc(sizeof(var));
        var_copy(to_ret, element_at(target, 0));
        target->min_index++;
        target->size--;
        if (debug) {
            printf("List now: ");
            for (int i = target->min_index; i < target->size + target->min_index; i++) {
                printf("%s ", getvar_str_fv(element_at(target, i)));
            }
            printf("\n");
        }
        return to_ret;
    } else {
        if (debug) printf("But it is empty!");
        return NULL;
    }
}

void list_copy(list *dest, list *src) {
    if (debug) printf("\nCopying list...\n");
    for (int i = 0; i < src->size; i++) {
        if (debug) printf("Copying element %d.\n", i);
        list_push(dest, element_at(src, i));
    }
    if (debug) printf("Done copying list, all good.\n");
}

var *element_at(list *target, int index) {
    if (index < 0 || index > target->size-1) {
        printf("Element index out of range: %d!\n", index);
        return newvar_empty_list();
    }
    return &(target->contents[index + target->min_index]);
}

int set_element(list *target, int index, var *value) {
    if (index < 0) {
        return -1;
    }
    if (index > target->size) {
        while (target->size < index - 1) {
            list_push(target, newvar_nothing());
        }
    }
    var_assign_fv(element_at(target, index), value);
    return 0;
}

list *alloc_list() {
    list *retval = malloc(sizeof(list));
    retval->max_size = 4;
    retval->size = 0;
    retval->min_index = 0;
    retval->contents = malloc(retval->max_size * sizeof(var));
    return retval;
}

list *alloc_list_size(int size) {
    list *retval = malloc(sizeof(list));
    retval->max_size = size;
    retval->size = 0;
    retval->min_index = 0;
    retval->contents = malloc(retval->max_size * sizeof(var));
    return retval;
}

void free_list(list *l) {
    var *elem;
    if (debug) printf("Free a list at %p.\n", (void*)l);
    for (int i = 0; i < l->size + l->min_index; i++) {
        elem = &l->contents[i];
        if (debug) printf("Free element %d -> %p.\n", i, (void*)elem);
        if (elem->str_equiv) {
            free(elem->str_equiv);
        }
        if (elem->type == LIST) {
            free_list(elem->content.l);
        } else if (elem->type == STRING) {
            free(elem->content.s);
        }
        if (debug) printf("Done.\n");
    }
    /* this free() will actually free all of them
       because they're allocated in a contiguous
       block */
    free(l->contents);
    if (debug) printf("Now going to free %p.\n", (void*)l);
    free(l);
    if (debug) printf("OK!\n");
}

void var_copy (var *dest, var *src) {
    *dest = *src;
    /* copy the string part as well so the pointer doesn't get freed twice */
    if (src->str_equiv != NULL) {
        char *newstr = malloc((strlen(src->str_equiv)+1) * sizeof(char));
        strcpy(newstr, src->str_equiv);
        dest->str_equiv = newstr;
    }
    if (src->type == LIST) {
        dest->content.l = alloc_list_size(src->content.l->size);
        list_copy(dest->content.l, src->content.l);
    } else if (src->type == STRING) {
        dest->content.s = malloc((strlen(src->content.s)+1)*sizeof(char));
        strcpy(dest->content.s, src->content.s);
    }
}
