#ifndef TYPES_LONG_SS_H
#define TYPES_LONG_SS_H

#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef STATIC
#  define STATIC static __attribute__((unused))
#endif

typedef struct long_ss {
    char s[64];
} long_ss;

typedef enum long_err_e {
    LONG_ERR_NULL_VALUE     = 0,
    LONG_ERR_INVALID_NUMBER = 1,
    LONG_ERR_OUT_OF_BOUNDS  = 2,
    LONG_ERR_MAX            = 3
} long_err_e;


STATIC bool
long_parse (long *_out, const char *_s, long_err_e *_opt_reason) {
    char *p;
    if (_s == NULL) goto fail_null_value;
    *_out = strtol(_s, &p, 10);
    if (*p != '\0') goto fail_invalid_number;
    if ((*_out) == LONG_MIN || (*_out) == LONG_MAX) goto fail_out_of_bounds;
    return true;
 fail_null_value:
    if (_opt_reason) *_opt_reason = LONG_ERR_NULL_VALUE;
    return false;
 fail_invalid_number:
    if (_opt_reason) *_opt_reason = LONG_ERR_INVALID_NUMBER;
    return false;
 fail_out_of_bounds:
    if (_opt_reason) *_opt_reason = LONG_ERR_OUT_OF_BOUNDS;
    return false;
}

STATIC bool
ulong_parse (unsigned long *_out, const char *_s, long_err_e *_opt_reason) {
    char *p;
    if (_s == NULL) goto fail_null_value;
    *_out = strtoul(_s, &p, 10);
    if (*p != '\0') goto fail_invalid_number;
    if ((*_out) == ULONG_MAX) goto fail_out_of_bounds;
    return true;
 fail_null_value:
    if (_opt_reason) *_opt_reason = LONG_ERR_NULL_VALUE;
    return false;
 fail_invalid_number:
    if (_opt_reason) *_opt_reason = LONG_ERR_INVALID_NUMBER;
    return false;
 fail_out_of_bounds:
    if (_opt_reason) *_opt_reason = LONG_ERR_OUT_OF_BOUNDS;
    return false;
}

STATIC const char *
long_str (long _n, long_ss *_ss) {
    sprintf(_ss->s, "%li", _n);
    return _ss->s;
}

STATIC const char *
ulong_str (unsigned long _n, long_ss *_ss) {
    sprintf(_ss->s, "%ld", _n);
    return _ss->s;
}

#endif
