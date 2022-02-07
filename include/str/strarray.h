#ifndef STRARRAY_H
#define STRARRAY_H

#include <stdbool.h>
#include <string.h>

typedef int (*strcmp_f) (const char *s1, const char *s2);

static inline
void streq2map(char *_i[], int _o_sz, char *_o[_o_sz]) {
    int f,t; char *v1,*v2;
    for (f=0, t=0; _i[f] && t<(_o_sz-3); f++) {
        v1 = _i[f];
        if ((v2 = strchr(v1, '='))) *(v2++) = '\0';
        _o[t++] = v1;
        _o[t++] = v2;
    }
    _o[t] = NULL;
}

static inline
char *strmap_get(char *_a[], const char _key[], strcmp_f _cmp) {
    for (char **e = _a; *e; e+=2) {
        if (*(e+1) && !_cmp(_key,*e)) {
            return *(e+1);
        }
    }
    return NULL;
}

#endif
