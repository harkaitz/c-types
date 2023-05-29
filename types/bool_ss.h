#ifndef TYPES_BOOL_SS_H
#define TYPES_BOOL_SS_H

#include <string.h>
#include <stdbool.h>

__attribute__((weak))
const char *g_true_values[] = {
    "true","t","y","yes",NULL
};
__attribute__((weak))
const char *g_false_values[] = {
    "false", "f", "n", "no",NULL
};

static __attribute__((unused)) bool
bool_parse (bool *_opt_out, const char *_in, const char **_opt_reason) {
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
    if (_opt_reason) *_opt_reason = "Invalid value";
    return false;
 fail_null_value:
    if (_opt_reason) *_opt_reason = "NULL value";
    return false;
}

static inline const char *
bool_str (bool _in) {
    return (_in)?g_true_values[0]:g_false_values[0];
}

static inline const char *
bool_str2(bool _in, const char *_true, const char *_false) {
    return (_in)?_true:_false;
}


#endif
