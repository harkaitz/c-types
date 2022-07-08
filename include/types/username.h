#ifndef TYPES_USERNAME_H
#define TYPES_USERNAME_H


#include <stdbool.h>
#include <string.h>

#ifdef NO_GETTEXT
#  define USERNAME_T(T) (T)
#else
#  include <libintl.h>
#  define USERNAME_T(T) dgettext("c-types", T)
#endif


typedef struct username username;
struct username { char s[64]; };

static __attribute__((unused)) bool
username_is_valid_str (const char _s[], const char **_opt_reason) {
    size_t i;
    if (!_s || !_s[0]) {
        if (_opt_reason) *_opt_reason = USERNAME_T("No username");
        return false;
    }
    for (i=0; _s[i]; i++) {
        if (strchr("/\\\"'%$\n\r \t", _s[i])) {
            goto invalid_username;
        } else if (i>sizeof(char [64])-1) {
            goto invalid_username;
        }
    }
    if (i<8) {
        goto invalid_username;
    }
    return true;
 invalid_username:
    if (_opt_reason) *_opt_reason = USERNAME_T("Invalid username");
    return false;
}

static inline bool
username_is_valid(const username *_e, const char **_opt_reason) {
    return username_is_valid_str(_e->s, _opt_reason);
}

static inline bool
username_parse (username *_u, const char _s[], const char **_opt_reason) {
    if (!username_is_valid_str(_s, _opt_reason)) return false;
    strcpy(_u->s, _s);
    return true;
}

static inline const char *
username_str(username *_u) {
    return _u->s;
}


#endif
