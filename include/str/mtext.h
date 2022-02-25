#ifndef STR_MTEXT_H
#define STR_MTEXT_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <syslog.h>

typedef struct mtext {
    const char *s[10];
} mtext;

__attribute__((weak)) struct {
    size_t        textsz;
    mtext        *texts[30];
} g_mtext = {0};
__attribute__((weak)) __thread char g_mtext_lang[10] = "en";


static inline void
mtext_add(mtext _t[]) {
    g_mtext.texts[g_mtext.textsz++] = _t;
}

static inline const char *
mtext_shift(const char _txt[]) {
    if (!strncasecmp(_txt, "T:", 2)) {
        return _txt+2;
    } else {
        return _txt;
    }
}

static inline const char *
mtext_get(const char _key[]) {
    size_t t,c_found,c,r;
    const char *f;
    for (t=0; t<g_mtext.textsz; t++,c_found = -1) {
        for (c=0; g_mtext.texts[t][0].s[c]; c++) {
            if (!strcasecmp("link", g_mtext.texts[t][0].s[c])) {
                c_found = c;
                break;
            } else if (!strcasecmp(g_mtext_lang, g_mtext.texts[t][0].s[c])) {
                c_found = c;
                break;
            }
        }
        if (c_found!=-1) {
            for (r=1; g_mtext.texts[t][r].s[0]; r++) {
                if (!strcasecmp(_key, g_mtext.texts[t][r].s[0])) {
                    f = g_mtext.texts[t][r].s[c_found];
                    if (f) return mtext_shift(f);
                }
            }
        }
    }
    syslog(LOG_WARNING, "Lang %s: Missing mtext: %s", g_mtext_lang, _key);
    return mtext_shift(_key);
}

static inline const char *
mtext_lang(void) {
    return g_mtext_lang;
}

static inline void
mtext_set_lang(const char _lang[]) {
    strncpy(g_mtext_lang, _lang, sizeof(g_mtext_lang)-1);
}



#ifndef _
#  define _(S) mtext_get(("MTEXT:" S "\x00:MTEXT-END") + sizeof("MTEXT:")-1)
#endif

#endif
