#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "uthash.h"

#define class_setup(classname, parent, setupfunc) do { \
    classname = malloc(sizeof(class)); \
    setupfunc ( (classname), (parent) ); \
} while(0)


struct class;
struct list;
struct var;

typedef struct var *(*builtin_method)(struct var*, struct list*);
typedef struct var *(*builtin_function)(struct list*);

/* A list of pointers to var objects. This is a dynamically
 * resizing array rather than a linked list.
 */
typedef struct list {
    struct var **head;
    int max_size;
    int size;
} list;

/* A tagged union that can take many different
 * data types.
 */
typedef struct var {
    struct class *class;
    union {
        char *s;
        int i;
        double fl;
        list *l;
        struct function *f;
        struct class *c;
    } ct; /* Content */
    struct binding *props; /* Object properties */
    int refs;
} var;

/* A function that can be called. This structure
 * allows built-in functions to exist on the same
 * level as user-defined ones (not implemented yet.)
 */
typedef struct function {
    union {
        var *(*builtin)(list *params);
        var *(*builtin_method)(var *self, list *params);
    } body;
    int is_builtin;
    int is_method;
} function;

/* A match between a name and a variable in the
 * current scope.
 */
typedef struct binding {
    var *v;
    char name[64];
    UT_hash_handle hh;
} binding;

/* This is a scope. It forms part of a linked list
 * of enclosing scopes that goes all the way out to the
 * outermost one.
 */
typedef struct scope {
    /* This is the scope's enclosing scope. */
    struct scope *outer;
    /* This represents the bindings for the scope. */
    binding *vars;
    /* This is the value of the last expression
       executed within the scope; it is also set
       on function return. */
    var *last_val;
} scope;

/* A class. It has a name, a hash table of bindings,
 * and a parent class that it inherits from.
 * It also should have a method to initialize it
 * (i.e. put all its data in the hashtable.)
 */
typedef struct class {
    struct class *parent;
    binding *vars;
    char name[64];
} class;

/* classes */
extern class *Obj;          /* : null */
extern class *Undefined;    /* : Obj */
extern class *Integer;      /* : Obj */
extern class *Function;     /* : Obj */
extern class *List;         /* : Obj */
extern class *String;       /* : Obj */
extern class *Class;        /* : Obj */

/* list.c defs */
extern list  *list_new();
extern void   list_push (list *l, var *v);
extern void   list_dump (list *l);
extern var   *list_get(list *l, int index);
extern void   list_free(list *l);

/* var.c defs */
extern var   *var_new();
extern void   var_set_int(var *to_set, int i);
extern void   var_set_func(var *to_set, function *f);
extern void   var_set_str(var *to_set, char *str);
extern void   var_set_list(var *to_set, list *l);
extern var   *var_call_method(var *v, char *name, list *params);
extern var   *var_get_prop(var *v, char *name);
extern void   var_dump(var *v);
extern char  *var_to_str(var *v);
extern void   var_unref(var *v);
extern void   var_check_refs(var *v);
extern void   var_free(var *v);

/* function.c defs */
extern var   *func_call(function *f, var *self, list *params);
extern void   func_set_builtin(function *f, builtin_function b);
extern void   func_set_builtin_method(function *f, builtin_method b);
extern void   func_param_check(char *func_name, int expected, list *params);

/* bind.c defs */
extern binding *binding_new();
extern void   bind(binding *b, var *v);
extern void   scope_bind(scope *sc, var *v, char *name);
extern void   class_bind(class *cl, var *v, char *name);
extern void   unbind(scope *current_scope, binding *b);
extern scope *scope_new(scope **current_scope_ptr);
extern void   scope_pop(scope **current_scope_ptr);
extern var   *scope_get_var(scope *scope, char *name);

/* class.c defs */
extern var   *class_find_item(class *cl, char *name);
extern void   class_add_method(class *cl, builtin_method m, char *name);
extern void   class_set_name(class *cl, char *name);
extern void   class_set_parent(class *child, class *parent);
extern void   class_free(class *cl);

/* gen.c defs */
extern void   gen_error (const char *format, ...);

/* lib.c defs */
extern var   *ap_print(list *params);
extern void   obj_class_init(class *obj, class *parent);
extern void   integer_class_init(class *integer, class *parent);
extern void   function_class_init(class *function, class *parent);
extern void   undefined_class_init(class *undef, class *parent);
extern void   list_class_init(class *list, class *parent);
extern void   string_class_init(class *string, class *parent);
extern void   class_class_init(class *_class, class *parent);
