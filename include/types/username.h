#ifndef TYPES_USERNAME_H
#define TYPES_USERNAME_H

#include "../io/slog.h"
#include <stdbool.h>
#include <string.h>


typedef struct username username;
struct username { char s[64]; };

static __attribute__((unused)) bool
username_is_valid_str (const char _s[], const char **_opt_reason) {
    size_t i;
    if (!_s) {
        error_reason(_opt_reason, "Null username.");
        return false;
    }
    for (i=0; _s[i]; i++) {
        if (strchr("/:\\\"'%$\n\r \t", _s[i])) {
            error_reason(_opt_reason, "Invalid characters in username");
            return false;
        } else if (i>sizeof(char [64])-1) {
            error_reason(_opt_reason, "Username too large.");
            return false;
        }
    }
    if (i<8) {
        error_reason(_opt_reason, "Username too small.");
        return false;
    }
    return true;
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
