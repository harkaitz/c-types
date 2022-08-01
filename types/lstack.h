#ifndef ALGO_STACK_H
#define ALGO_STACK_H

#include <stdbool.h>
#include <stdlib.h>

static inline bool
lstack_push (size_t *_pos, long _b[], size_t _bsz, long _d) {
    size_t nsize = ((*_pos)+1)*sizeof(long);
    if (nsize > _bsz) return false;
    _b[(*_pos)++] = _d;
    return true;
}

static inline bool
lstack_get (const size_t *_pos, long _b[], long *_d) {
    if (*_pos == 0) return false;
    if (_d) *_d = _b[(*_pos)-1];
    return true;
}

static inline bool
lstack_pop (size_t *_pos, long _b[], long *_d) {
    if (!lstack_get(_pos, _b, _d)) return false;
    --(*_pos);
    return true;
}

#endif
