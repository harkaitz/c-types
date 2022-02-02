#ifndef MCONFIG_H
#define MCONFIG_H

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdarg.h>

#define MCONFIG_LIMIT 100

typedef struct mconfig_s       mconfig_t;

struct mconfig_s {
    const char *v[MCONFIG_LIMIT];
    size_t      vsz;
};

#define MCONFIG_INITIALIZER() {0}

static __attribute__((unused)) void
mconfig_cleanup(mconfig_t *_m) {
    for (size_t i=0; i<_m->vsz; i++) {
        free((void*)_m->v[i]);
    }
    _m->vsz=0;
}

static __attribute__((unused)) bool
mconfig_search(mconfig_t *_m, size_t *_opt_var, size_t *_opt_val, const char _var[]) {
    for(size_t i=0; i<_m->vsz; i+=2) {
        if (_m->v[i] && _m->v[i+1] && !strcasecmp(_var, _m->v[i])) {
            if (_opt_var) *_opt_var = i;
            if (_opt_val) *_opt_val = i+1;
            return true;
        }
    }
    return false;
}

static __attribute__((unused, sentinel)) bool
mconfig_add(mconfig_t *_m, ...) {
    bool    retval = false;
    va_list va;
    va_start(va, _m);
    while (1) {
        if (_m->vsz >= (MCONFIG_LIMIT-5)) goto fail_too_much_settings;
        const char *var = va_arg(va, const char *); if (!var) break;
        const char *val = va_arg(va, const char *); if (!val) break;
        char *var_m = strdup(var);
        if (!var_m) goto fail_errno;
        char *val_m = strdup(val);
        if (!val_m) goto fail_errno;
        _m->v[_m->vsz++] = var_m;
        _m->v[_m->vsz++] = val_m;
        _m->v[_m->vsz]   = NULL;
    }
    retval = true;
 cleanup:
    va_end(va);
    return retval;
 fail_errno:
    syslog(LOG_ERR, "%s", strerror(errno));
    goto cleanup;
 fail_too_much_settings:
    syslog(LOG_ERR, "Too much settings.");
    goto cleanup;
}

static __attribute__((unused)) bool
mconfig_load(mconfig_t *_m, const char _filename[], bool _success_if_not_found) {
    bool               retval   = false;
    FILE              *fp       = NULL;
    char               b[1024]  = {0};
    int                ln       = 0;
    char              *l,*_l,*c1,*c2;
    fp = fopen(_filename, "r");
    if (fp == NULL && errno == ENOENT && _success_if_not_found) {
        return true;
    }
    if (!fp/*err*/) { goto fail_errno; }
    for (ln=1; (l = fgets(b, sizeof(b)-1, fp)); ln++) {
        if ((c1 = strchr(l, '#'))) *c1 = '\0';
        if (!(c1 = strtok_r(l, " \t\n", &_l))) continue;
        c2 = strtok_r(0, " \t\n", &_l);
        if (!c2/*err*/) goto fail_no_value;
        if (mconfig_search(_m, NULL, NULL, c1)) continue;
        if (!mconfig_add(_m, c1, c2, NULL)) goto cleanup;
    }
    retval = true;
 cleanup:
    if (fp) fclose(fp);
    return retval;
 fail_errno:
    syslog(LOG_ERR, "%s: %s", _filename, strerror(errno));
    goto cleanup;
 fail_no_value:
    syslog(LOG_ERR, "%s: %-3i: %s", _filename, ln, strerror(errno));
    goto cleanup;
}

static __attribute__((unused)) const char *
mconfig_get(mconfig_t *_m, const char _var[], const char _def[]) {
    size_t f;
    return (mconfig_search(_m, NULL, &f, _var))?_m->v[f]:_def;
}

static __attribute__((unused, sentinel)) int
mconfig_printf(mconfig_t *_m, FILE *_f, const char _cfg[], ...) {
    va_list     va;
    int         r = 0;
    const char *c;
    va_start(va, _cfg);
    for (c = _cfg; c; c=va_arg(va, const char*)) {
        r += fprintf(_f, "%-30s %s\n", c, mconfig_get(_m, c, ""));
    }
    va_end(va);
    return r;
}

static __attribute__((unused, sentinel)) bool
mconfig_require(mconfig_t *_m, ...) {
    bool          ret = true;
    const char   *var,*help;
    va_list       va;
    va_start(va, _m);
    while (1) {
        if (!(var=va_arg(va, const char*)) || !(help = va_arg(va, const char*))) {
            break;
        } else if (!mconfig_search(_m, NULL, NULL, var)) {
            syslog(LOG_ERR, "Config '%s' not set: %s", var, help);
            break;
        }
    }
    va_end(va);
    return ret;
}

#endif
/**l*
 * 
 * This software is free to use and modify, but not free to maintain.
 * 
 * Donate bitcoin: 1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV
 * Donate monero: 88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti
 * Copyright (c) 2022 Harkaitz Agirre, harkaitz.aguirre@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **l*/
