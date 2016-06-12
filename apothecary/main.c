#include "apothecary.h"

class *Class;
class *Function;
class *Integer;
class *List;
class *Obj;
class *String;
class *Undefined;

int main(void) {
    scope *current_scope = NULL;
    scope_new(&current_scope);

    setbuf(stdout, NULL);

    Class = malloc(sizeof(class));
    Function = malloc(sizeof(class));
    Integer = malloc(sizeof(class));
    List = malloc(sizeof(class));
    Obj = malloc(sizeof(class));
    String = malloc(sizeof(class));
    Undefined = malloc(sizeof(class));

    obj_class_init(Obj, NULL);
    class_class_init(Class, Obj);
    integer_class_init(Integer, Obj);
    function_class_init(Function, Obj);
    list_class_init(List, Obj);
    string_class_init(String, Obj);
    undefined_class_init(Undefined, Obj);

    /* Variable dumping test. */
    list *l = list_new();
    var *v1 = var_new();
    var *v2 = var_new();
    var *v3 = var_new();
    var_set_int(v1, 503);
    function *print = malloc(sizeof(function));
    func_set_builtin(print, &ap_print);
    var_set_func(v2, print);
    list_push(l, v1);
    list_push(l, v2);
    list_push(l, v3);
    list_dump(l);

    /* Addition/method-calling test. */
    var *num = var_new();
    var_set_int(num, 23);
    list *l2 = list_new();
    list_push(l2, v1);
    var *sum = var_call_method(num, "__add", l2);
    var_dump(sum);
    var_free(sum);
    printf("\n");
    list_free(l2);

    /* Property get/set test. */
    var *proper = var_new();
    list *propset_params = list_new();
    list *propget_params = list_new();
    list *print_params = list_new();
    var *prop_name = var_new();
    var_set_str(prop_name, "foo");
    var *prop_val = var_new();
    var_set_str(prop_val, "bar");
    list_push(propset_params, prop_name);
    list_push(propset_params, prop_val);
    list_push(propget_params, prop_name);
    var_call_method(proper, "__prop_set", propset_params);
    var *result = var_call_method(proper, "__prop_get", propget_params);
    list_push(print_params, result);
    func_call(v2->ct.f, NULL, print_params); /* Print */
    list_free(propset_params);
    list_free(propget_params);
    list_free(print_params);
    var_check_refs(proper);
    printf("\n");

    /* Scoping test. */
    scope_bind(current_scope, num, "x");
    scope_new(&current_scope);
    scope_bind(current_scope, v1, "x");
    list *print_params2 = list_new();
    list_push(print_params2, scope_get_var(current_scope, "x"));
    func_call(v2->ct.f, NULL, print_params2);
    printf("\n");
    scope_pop(&current_scope);
    free(print_params2->head);
    free(print_params2);
    print_params2 = list_new();
    list_push(print_params2, scope_get_var(current_scope, "x"));
    func_call(v2->ct.f, NULL, print_params2);
    printf("\n");
    list_free(print_params2);

    /* Call the function in the list */
    func_call(list_get(l, 1)->ct.f, NULL, l);

    /* Cleanup */
    list_free(l);
    var_unref(v1);
    scope_pop(&current_scope);
    printf("\n");

    class_free(Undefined);
    class_free(Integer);
    class_free(List);
    class_free(String);
    class_free(Function);
    class_free(Class);
    class_free(Obj);
}
