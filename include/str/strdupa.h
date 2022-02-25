#ifndef STRDUPA_H
#define STRDUPA_H

#include <stdlib.h>

#define strdupa(S) ({                           \
            const char *__s = (S);              \
            size_t      __l = strlen(__s)+1;    \
            char       *__m = alloca(__l);      \
            memcpy(__m, __s, __l);              \
            __m;                                \
        })
#define strcata(...) ({                                     \
            const char *__a[] = {__VA_ARGS__};              \
            size_t      __c   = sizeof(__a)/sizeof(__a[0]); \
            char       *__m;                                \
            size_t      __w[__c];                           \
            size_t      __l   = 0;                          \
            for (int i=0; i<__c; i++) {                     \
                __w[i] = strlen(__a[i]);                    \
                __l += __w[i];                              \
            }                                               \
            __m = alloca(__l+1); __l = 0;                   \
            for (int i=0; i<__c; i++) {                     \
                memcpy(__m+__l, __a[i], __w[i]);            \
                __l += __w[i];                              \
            }                                               \
            __m[__l] = '\0';                                \
            __m;                                            \
        })



#endif
