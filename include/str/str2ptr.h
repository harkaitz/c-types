#ifndef STR_STR2PTR_H
#define STR_STR2PTR_H

#include <stdarg.h>
#include <stdlib.h>

static inline __attribute__((sentinel))
void *str2ptr(const char *s1, int (*f) (const char *,const char *), ...) {
    const char *s2     = NULL;
    void       *v2     = 0;
    void       *retval = NULL;
    va_list     va;
    if (s1 && f) {
        va_start(va, s1);
        while (1) {
            s2 = va_arg(va, const char *);
            if (!s2) break;
            v2 = va_arg(va, void *);
            if (f(s1,s2)) continue;
            retval = v2;
            break;
        }
        va_end(va);
    }
    return retval;
}
    

#endif
