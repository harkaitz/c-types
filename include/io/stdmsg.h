#ifndef STDMSG_H
#define STDMSG_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

__attribute__((weak)) __thread FILE *g_stdmsg_fp = NULL;


__attribute__((weak))
void stdmsgv(const char _fmt[], va_list va) {
    if (g_stdmsg_fp) {
        vfprintf(g_stdmsg_fp, _fmt, va);
        fputc('\n', g_stdmsg_fp);
    }
}

static inline
void stdmsg(const char _fmt[], ...) {
    va_list va;
    va_start(va, _fmt);
    stdmsgv(_fmt, va);
    va_end(va);
}

static inline
void stdmsg_set(FILE *_opt_fp, FILE **_opt_old_fp) {
    if (_opt_old_fp) {
        *_opt_old_fp = g_stdmsg_fp;
    } else if (g_stdmsg_fp) {
        fclose(g_stdmsg_fp);
    }
    g_stdmsg_fp = _opt_fp;
}


#endif
