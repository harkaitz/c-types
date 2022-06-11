#ifndef TYPES_LONG_SS_H
#define TYPES_LONG_SS_H

#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "../io/slog.h"

typedef struct long_ss {
    char s[64];
} long_ss;

static __attribute__((unused)) bool
long_parse (long *_out, const char *_s, const char **_reason) {
    char *p;
    if (_s == NULL/*err*/) {
        error_reason(_reason, NO_NUMBER, "No number");
        return false;
    }
    *_out = strtol(_s, &p, 10);
    if (*p != '\0'/*err*/) {
        error_reason(_reason, INVALID_NUMBER, "Invalid number");
        return false;
    }
    if ((*_out) == LONG_MIN || (*_out) == LONG_MAX/*err*/) {
        error_reason(_reason, OUT_OF_BOUNDS, "Out of bounds");
        return false;
    }
    return true;
}

static __attribute__((unused)) bool
ulong_parse (unsigned long *_out, const char *_s, const char **_reason) {
    char *p;
    if (_s == NULL/*err*/) {
        error_reason(_reason, NO_NUMBER, "No number");
        return false;
    }
    *_out = strtoul(_s, &p, 10);
    if (*p != '\0'/*err*/) {
        error_reason(_reason, INVALID_NUMBER, "Invalid number");
        return false;
    }
    if ((*_out) == ULONG_MAX/*err*/) {
        error_reason(_reason, OUT_OF_BOUNDS, "Out of bounds");
        return false;
    }
    return true;
}

static inline const char *
long_str (long _n, long_ss *_ss) {
    sprintf(_ss->s, "%li", _n);
    return _ss->s;
}

static inline const char *
ulong_str (unsigned long _n, long_ss *_ss) {
    sprintf(_ss->s, "%ld", _n);
    return _ss->s;
}

#endif
