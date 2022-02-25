#ifndef STRARRAY_H
#define STRARRAY_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

static inline
void strmap_free(char *_a[]) {
    for (char **p = _a; *p; p++) {
        free(*p);
    }
}

static inline
int strmap_malloc(char *_a[]) {
    for (char **p = _a; *p; p++) {
        if (!(*p = strdup(*p))) {
            strmap_free(_a);
            return -1;
        }
    }
    return 0;
}

#endif
