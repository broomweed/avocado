#include "avocado.h"

/* var arithmetic/operators */
var *vars_sum(var *v1, var *v2);
var *vars_diff(var *v1, var *v2);
var *vars_product(var *v1, var *v2);
var *vars_quotient(var *v1, var *v2);
var *vars_concat(var *v1, var *v2);
var *vars_cmp(var *v1, var *v2, enum asttypes type);


var *vars_sum(var *v1, var *v2) {
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.d+v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl(v1->content.d+v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl(v1->content.d+atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.i+v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(v1->content.i+v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(v1->content.i+atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(atoi(v1->content.s)+v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(atoi(v1->content.s)+v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(atoi(v1->content.s)+atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else {
        return newvar_int(0);
    }
}

var *vars_diff(var *v1, var *v2) {
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.d-v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl(v1->content.d-v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl(v1->content.d-atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.i-v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(v1->content.i-v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(v1->content.i-atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(atoi(v1->content.s)-v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(atoi(v1->content.s)-v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(atoi(v1->content.s)-atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else {
        return newvar_int(0);
    }
}

var *vars_product(var *v1, var *v2) {
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.d*v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl(v1->content.d*v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl(v1->content.d*atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.i*v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(v1->content.i*v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(v1->content.i*atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(atoi(v1->content.s)*v2->content.d);
        } else if (v2->type == INT) {
            return newvar_int(atoi(v1->content.s)*v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_int(atoi(v1->content.s)*atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else {
        return newvar_int(0);
    }
}

var *vars_quotient(var *v1, var *v2) {
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            return newvar_dbl(v1->content.d/v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl(v1->content.d/v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl(v1->content.d/atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            return newvar_dbl((double)v1->content.i/v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl((double)v1->content.i/v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl((double)v1->content.i/atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            return newvar_dbl((double)atoi(v1->content.s)/v2->content.d);
        } else if (v2->type == INT) {
            return newvar_dbl((double)atoi(v1->content.s)/v2->content.i);
        } else if (v2->type == STRING) {
            return newvar_dbl((double)atoi(v1->content.s)/atoi(v2->content.s));
        } else {
            return newvar_int(0);
        }
    } else {
        return newvar_int(0);
    }
}

var *vars_concat(var *v1, var *v2) {
    int len1, len2;
    char *strtoret;
    var *vartoret;
    if (v1->type == STRING) len1 = strlen(getvar_str_fv(v1));
    else len1 = 16;
    if (v2->type == STRING) len2 = strlen(getvar_str_fv(v2));
    else len2 = 16;
    strtoret = (char*)malloc((len1 + len2 + 1) * sizeof(char));
    if (v1->type == DOUBLE) {
        if (v2->type == DOUBLE) {
            sprintf(strtoret, "%g%g", v1->content.d, v2->content.d);
        } else if (v2->type == INT) {
            sprintf(strtoret, "%g%d", v1->content.d, v2->content.i);
        } else if (v2->type == STRING) {
            sprintf(strtoret, "%g%s", v1->content.d, v2->content.s);
        } else {
            sprintf(strtoret, "%g", v1->content.d);
        }
    } else if (v1->type == INT) {
        if (v2->type == DOUBLE) {
            sprintf(strtoret, "%d%g", v1->content.i, v2->content.d);
        } else if (v2->type == INT) {
            sprintf(strtoret, "%d%d", v1->content.i, v2->content.i);
        } else if (v2->type == STRING) {
            sprintf(strtoret, "%d%s", v1->content.i, v2->content.s);
        } else {
            sprintf(strtoret, "%d", v1->content.i);
        }
    } else if (v1->type == STRING) {
        if (v2->type == DOUBLE) {
            sprintf(strtoret, "%s%g", v1->content.s, v2->content.d);
        } else if (v2->type == INT) {
            sprintf(strtoret, "%s%d", v1->content.s, v2->content.i);
        } else if (v2->type == STRING) {
            sprintf(strtoret, "%s%s", v1->content.s, v2->content.s);
        } else {
            sprintf(strtoret, "%s", v1->content.s);
        }
    } else {
        if (v2->type == DOUBLE) {
            sprintf(strtoret, "%g", v2->content.d);
        } else if (v2->type == INT) {
            sprintf(strtoret, "%d", v2->content.i);
        } else if (v2->type == STRING) {
            sprintf(strtoret, "%s", v2->content.s);
        } else {
            free(strtoret);
            return newvar_str("");
        }
    }
    /* because newvar_str strcpy's its argument */
    vartoret = newvar_str(strtoret);
    free(strtoret);
    return vartoret;
}

var *vars_cmp(var *v1, var *v2, enum asttypes type) {
    switch (type) {
        case NUM_EQ:
            return newvar_boolean(getvar_double_fv(v1) == getvar_double_fv(v2));
        case NUM_NE:
            return newvar_boolean(getvar_double_fv(v1) != getvar_double_fv(v2));
        case NUM_GT:
            return newvar_boolean(getvar_double_fv(v1) > getvar_double_fv(v2));
        case NUM_LT:
            return newvar_boolean(getvar_double_fv(v1) < getvar_double_fv(v2));
        case NUM_GTEQ:
            return newvar_boolean(getvar_double_fv(v1) >= getvar_double_fv(v2));
        case NUM_LTEQ:
            return newvar_boolean(getvar_double_fv(v1) <= getvar_double_fv(v2));
        case STR_EQ:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) == 0);
        case STR_NE:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) != 0);
        case STR_GT:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) > 0);
        case STR_LT:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) < 0);
        case STR_GTEQ:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) >= 0);
        case STR_LTEQ:
            return newvar_boolean(strcmp(getvar_str_fv(v1), getvar_str_fv(v2)) <= 0);
        default:
            printf("I don't know how to compare by %c.\n", type);
            return NULL;
    }
}

