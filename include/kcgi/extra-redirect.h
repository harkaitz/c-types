#ifndef KCGI_EXTRA_REDIRECT_H
#define KCGI_EXTRA_REDIRECT_H

#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <kcgi.h>

static inline
void khttp_head_redirect(struct kreq *_k, const char *_url) {
    khttp_head(_k, kresps[KRESP_STATUS]  , "%s", khttps[KHTTP_302]);
    khttp_head(_k, kresps[KRESP_LOCATION], "%s", _url);
}

#endif
