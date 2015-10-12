#include "apothecary.h"

var *ap_print(list *params) {
    for (int i = 0; i < params->size; i++) {
        var *str = var_call_method(list_get(params, i), "__to_str", NULL);
        printf("%s", str->ct.s);
        var_free(str);
    }
}

/* ---- OBJ ---- */
var *_obj__to_str(var *self, list *params) {
    var *new_str = var_new();
    new_str->ct.s = malloc(128*sizeof(char));
    new_str->class = String;
    sprintf(new_str->ct.s, "<%s %p>", self->class->name, self);
    return new_str;
}

var *_obj__prop_get(var *self, list *params) {
    func_param_check("Object::__prop_get", 1, params);
    var *key = list_get(params, 0);
    var *retval = var_get_prop(self, key->ct.s);
    if (retval) {
        return retval;
    } else {
        gen_error("object of class '%s' has no property '%s'.", self->class->name, key->ct.s);
    }
}

var *_obj__prop_set(var *self, list *params) {
    func_param_check("Object::__prop_set", 2, params);
    var *key = list_get(params, 0);
    var *val = list_get(params, 1);
    binding *prop;
    HASH_FIND_STR(self->props, key->ct.s, prop);
    if (prop) {
        bind(prop, val);
    } else {
        binding *b = binding_new();
        b->v = NULL;
        bind(b, list_get(params, 1));
        strncpy(b->name, key->ct.s, 64);
        HASH_ADD_STR(self->props, name, b);
    }
    return val;
}

void obj_class_init(class *_obj, class *parent) {
    _obj->vars = NULL;
    class_add_method(_obj, &_obj__to_str, "__to_str");
    class_add_method(_obj, &_obj__prop_get, "__prop_get");
    class_add_method(_obj, &_obj__prop_set, "__prop_set");
    class_set_parent(_obj, parent);
    class_set_name(_obj, "Object");
}

/* ---- INTEGER ---- */
var *_integer__to_str(var *self, list *params) {
    var *new_str = var_new();
    new_str->ct.s = malloc(32*sizeof(char));
    sprintf(new_str->ct.s, "%d", self->ct.i);
    new_str->class = String;
    return new_str;
}

var *_integer__add(var *self, list *params) {
    func_param_check("Integer::__add", 1, params);
    var *new_int = var_new();
    var_set_int(new_int, self->ct.i + list_get(params, 0)->ct.i);
    return new_int;
}

void integer_class_init(class *_integer, class *parent) {
    _integer->vars = NULL;
    class_add_method(_integer, &_integer__to_str, "__to_str");
    class_add_method(_integer, &_integer__add, "__add");
    class_set_parent(_integer, parent);
    class_set_name(_integer, "Integer");
}

/* ---- FUNCTION ---- */
void function_class_init(class *function, class *parent) {
    function->vars = NULL;
    class_set_parent(function, parent);
    class_set_name(function, "Function");
}

/* ---- UNDEFINED ---- */
var *_undefined__to_str(var *self, list *params) {
    var *new_str = var_new();
    new_str->ct.s = malloc(10*sizeof(char));
    new_str->class = String;
    sprintf(new_str->ct.s, "undefined");
    return new_str;
}

void undefined_class_init(class *_undef, class *parent) {
    _undef->vars = NULL;
    class_add_method(_undef, &_undefined__to_str, "__to_str");
    class_set_parent(_undef, parent);
    class_set_name(_undef, "Undefined");
}

/* ---- LIST ---- */
var *_list__to_str(var *self, list *params) {
    var *new_str = var_new();
    int len = 0;
    list *l = self->ct.l;
    int i;
    var *str;
    for (i = 0; i < l->size; i++) {
        str = var_call_method(list_get(l, i), "__to_str", NULL);
        len += strlen(str->ct.s);
        var_free(str);
    }
    char *repr = malloc((len+1)*sizeof(char));
    repr[0] = '\0'; /* so that if len == 0 it just returns an empty string */
    len = 0;
    for (i = 0; i < l->size; i++) {
        str = var_call_method(list_get(l, i), "__to_str", NULL);
        sprintf(repr + len, "%s ", str->ct.s);
        len += strlen(str->ct.s) + 1;
        var_free(str);
    }
    var *to_ret = var_new();
    var_set_str(to_ret, repr);
    free(repr);
    return to_ret;
}

void list_class_init(class *list, class *parent) {
    list->vars = NULL;
    class_add_method(list, &_list__to_str, "__to_str");
    class_set_parent(list, parent);
    class_set_name(list, "List");
}

/* ---- STRING ---- */
var *_string__to_str(var *self, list *params) {
    var *new_str = var_new();
    var_set_str(new_str, self->ct.s);
    return new_str;
}

void string_class_init(class *string, class *parent) {
    string->vars = NULL;
    class_add_method(string, &_string__to_str, "__to_str");
    class_set_parent(string, parent);
    class_set_name(string, "String");
}

/* ---- CLASS ---- */
void class_class_init(class *_class, class *parent) {
    _class->vars = NULL;
    class_set_parent(_class, parent);
    class_set_name(_class, "Class");
}
