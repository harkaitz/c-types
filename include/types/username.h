#ifndef TYPES_USERNAME_H
#define TYPES_USERNAME_H

#include <stdbool.h>
#include <string.h>

#define USERNAME_LENGTH_LIMIT   64
#define USERNAME_LENGTH_MINIMUM 8

typedef struct username username;
struct username { char s[USERNAME_LENGTH_LIMIT+1]; };

static inline
bool username_parse (username *_u, const char _s[]) {
    strncpy(_u->s, _s, sizeof(_u->s)-1);
    return true;
}

#endif
