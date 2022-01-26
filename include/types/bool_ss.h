#ifndef TYPES_BOOL_SS_H
#define TYPES_BOOL_SS_H

#include <string.h>
#include <stdbool.h>

typedef enum bool_err_e {
    BOOL_ERR_NULL_VALUE    = 0,
    BOOL_ERR_INVALID_VALUE = 1,
    BOOL_ERR_MAX           = 2
} bool_err_e;

__attribute__((weak))
const char *g_true_values[] = {
    "true","t","y","yes",NULL
};
__attribute__((weak))
const char *g_false_values[] = {
    "false", "f", "n", "no",NULL
};

static __attribute__((unused)) bool
bool_parse (bool *_opt_out, const char *_in, bool_err_e *_opt_reason) {
    if (!_in) goto fail_null_value;
    for (const char **s = g_true_values; *s; s++) {
        if (!strcasecmp(_in, *s)) {
            if (_opt_out) *_opt_out = true;
            return true;
        }
    }
    for (const char **s = g_false_values; *s; s++) {
        if (!strcasecmp(_in, *s)) {
            if (_opt_out) *_opt_out = false;
            return true;
        }
    }
    goto fail_invalid_value;
 fail_invalid_value:
    if (_opt_reason) *_opt_reason = BOOL_ERR_INVALID_VALUE;
    return false;
 fail_null_value:
    if (_opt_reason) *_opt_reason = BOOL_ERR_NULL_VALUE;
    return false;
}

static __attribute__((unused)) const char *
bool_str (bool _in) {
    return (_in)?g_true_values[0]:g_false_values[0];
}



#endif
