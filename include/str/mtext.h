#ifndef STR_MTEXT_H
#define STR_MTEXT_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <syslog.h>

__attribute__((weak)) __thread char g_mtext_lang[10] = "en";

static inline const char *
mtext_lang(void) {
    return g_mtext_lang;
}

static inline void
mtext_set_lang(const char _lang[]) {
    strncpy(g_mtext_lang, _lang, sizeof(g_mtext_lang)-1);
}

static inline
const char *mtxt_search_word(const char **_a1, const char **_a2) {
    int i;
    if (_a2) {
        for (i=0; _a2[i]; i+=2) {
            if (_a2[i+1] && !strcmp(_a2[i], g_mtext_lang)) {
                return _a2[i+1];
            }
        }
    }
    if (_a1) {
        for (i=0; _a1[i]; i+=2) {
            if (_a1[i+1] && !strcmp(_a1[i], g_mtext_lang)) {
                return _a1[i+1];
            }
        }
        return _a1[1];
    }
    return "";
}

#define MTXT(KEY,TXT,...) ({                                        \
            extern __attribute__((weak)) const char *MTEXT_G_ ## KEY[]; \
            static                       const char *MTEXT_L_ ## KEY[] = {"en", TXT, ##__VA_ARGS__, NULL}; \
            const char *__s = mtxt_search_word(MTEXT_L_ ## KEY, MTEXT_G_ ## KEY); \
            __s;                                                        \
        })
#define MTXT_U(KEY) ({                                                  \
            extern const char *MTEXT_G_ ## KEY[];                       \
            const char *__s = mtxt_search_word(NULL, MTEXT_G_ ## KEY);  \
            __s;                                                        \
        })

#define MTXT_DEF(KEY,...) const char *MTEXT_G_ ## KEY[] = {__VA_ARGS__, NULL}






#endif
