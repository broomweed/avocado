#include "apothecary.h"

void gen_error (const char *format, ...) {
    va_list args;
    fprintf(stderr, "error: ");
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fprintf(stderr, "\nThe program will now abort. This behavior may change in future.\n");
    abort();
}
