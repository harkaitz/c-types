#ifndef MCONFIG_H
#define MCONFIG_H

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdarg.h>

typedef struct mconfig_s       mconfig_t;
typedef struct mconfig_field_s mconfig_field_t;

struct mconfig_s {
    mconfig_field_t *l;
};

struct mconfig_field_s {
    mconfig_field_t *next;
    char            *val;
    char             var[1];
};

#define MCONFIG_INITIALIZER() {0}

static __attribute__((unused)) void
mconfig_cleanup(mconfig_t *_m) {
    for(mconfig_field_t *e = _m->l,*n; e; e=n) {
        if (e->val) free(e->val);
        n = e->next;
        free(e);
    }
    memset(_m, 0, sizeof(mconfig_t));
}

static __attribute__((unused)) bool
mconfig_search(mconfig_t *_m, mconfig_field_t **_opt_f, const char _var[]) {
    for(mconfig_field_t *e = _m->l; e; e=e->next) {
        if (!strcasecmp(e->var, _var)) {
            if (_opt_f) *_opt_f = e;
            return true;
        }
    }
    return false;
}

static __attribute__((unused)) bool
mconfig_load(mconfig_t *_m, const char _filename[], bool _no_err_if_not_found) {
    bool               retval   = false;
    FILE              *fp       = NULL;
    char               b[1024]  = {0};
    int                line     = 0;
    char              *l,*_l,*c1,*c2;
    mconfig_field_t   *f;

    /* Open file. */
    fp = fopen(_filename, "rb");
    if (fp == NULL && errno == ENOENT && _no_err_if_not_found) {
        return true;
    }
    if (!fp) goto fail_errno;
    /* Read options. */
    for (line=1; (l = fgets(b, sizeof(b)-1, fp)); line++) {
        /* Remove comments. */
        if ((c1 = strchr(l, '#'))) {
            *c1 = '\0';
        }
        /* Get variable name. Skip empty lines. */
        c1 = strtok_r(l, " \t\n", &_l);
        if (!c1) {
            continue;
        }
        /* Get value. */
        c2 = strtok_r(0, " \t\n", &_l);
        if (!c2/*err*/) goto fail_no_value;
        /* Search previous variable, skip if it exists. */
        if (mconfig_search(_m, &f, c1)) {
            continue;
        }
        /* Allocate memory. */
        c2 = strdup(c2);
        if (!c2/*err*/) goto fail_errno;
        f = malloc(sizeof(mconfig_field_t)+strlen(c1)+1);
        if (!f/*err*/) { free(c2); goto fail_errno; }
        strcpy(f->var, c1);
        f->val = c2;
        /* Add to list. */
        f->next = _m->l;
        _m->l = f;
    }
    /* Cleanup. */
    retval = true;
 cleanup:
    if (fp) fclose(fp);
    return retval;
 fail_errno:
    syslog(LOG_ERR, "%s: %s", _filename, strerror(errno));
    goto cleanup;
 fail_no_value:
    syslog(LOG_ERR, "%s: %-3i: %s", _filename, line, strerror(errno));
    goto cleanup;
}

static __attribute__((unused)) const char *
mconfig_get(mconfig_t *_m, const char _var[], const char _def[]) {
    mconfig_field_t *f;
    return (mconfig_search(_m, &f, _var))?f->val:_def;
}

static __attribute__((unused)) bool
mconfig_set(mconfig_t *_m, const char _var[], const char _val[]) {
    char            *v = NULL;
    mconfig_field_t *f = NULL;
    if (!_val) return true;
    v = strdup(_val);
    if (!v/*err*/) goto fail_errno;
    if (mconfig_search(_m, &f, _var)) {
        f->val = v;
    } else {
        f = malloc(sizeof(mconfig_field_t)+strlen(_var)+1);
        if (!f/*err*/) { free(v); goto fail_errno; }
        strcpy(f->var, _var);
        f->val = v;
        f->next = _m->l;
        _m->l = f;
    }
    return true;
 fail_errno:
    syslog(LOG_ERR, "%s", strerror(errno));
    return false;
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
        } else if (!mconfig_search(_m, NULL, var)) {
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
