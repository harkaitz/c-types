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

static inline
int num2num(int _num, int _last, ...) {
    va_list        va;
    int            f1;
    int            f2;
    int            res = _last;
    va_start(va, _last);
    while ((f1 = va_arg(va, int)) != _last) {
        f2 = va_arg(va, int);
        if (f1 == _num) {
            res = f2;
            break;
        }
    }
    va_end(va);
    return res;
}

#endif
