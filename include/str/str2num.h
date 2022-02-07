#ifndef STR_STR2NUM_H
#define STR_STR2NUM_H

#include <stdarg.h>
#include <stdlib.h>

static inline __attribute__((sentinel))
int str2num(const char *s1, int (*f) (const char *,const char *), ...) {
    const char *s2     = NULL;
    int         v2     = 0;
    int         retval = -1;
    va_list     va;
    if (!s1) return -2;
    va_start(va, s1);
    while (1) {
        s2 = va_arg(va, const char *);
        if (!s2) break;
        v2 = va_arg(va, int);
        if (f(s1,s2)) continue;
        retval = v2;
        break;
    }
    va_end(va);
    return retval;
}

#endif
