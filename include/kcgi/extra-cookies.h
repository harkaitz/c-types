#ifndef KCGI_EXTRA_COOKIES_H
#define KCGI_EXTRA_COOKIES_H

#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <kcgi.h>

static inline
void khttp_head_del_cookie(struct kreq *_k, const char _n[]) {
    char  b[1024];
    char *t = khttp_epoch2str(0, b, sizeof(b)-1);
    khttp_head(_k, kresps[KRESP_SET_COOKIE], "%s=; Path=/; expires=%s", _n, t);
}

static inline
void khttp_head_set_cookie(struct kreq *_k, const char _n[], const char _v[]) {
    khttp_head(_k, kresps[KRESP_SET_COOKIE], "%s=%s; Path=/", _n, _v);
}

#endif
