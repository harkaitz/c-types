#ifndef STR_PHASH_H
#define STR_PHASH_H

#include <inttypes.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>

static inline __attribute__((unused))
uint64_t phashv(uint64_t opt_hash,const char *format,va_list va) {
    uint64_t hash = (opt_hash)?opt_hash:525201411107845655ull;
    for(const char *f=format;*f;f++) {
        if(*f=='s') {
            const unsigned char *c=va_arg(va,const unsigned char *);
            if(c) {
                for(;*c;c++) {
                    hash ^= *c;
                    hash *= 0x5bd1e9955bd1e995;
                    hash ^= hash >> 47u;
                }
            }
        } else if(*f=='b') {
            size_t l = va_arg(va, size_t);
            const unsigned char *c = va_arg(va, const unsigned char *);
            if(c && l) {
                for(size_t p=0;p<l;p++) {
                    hash ^= c[p];
                    hash *= 0x5bd1e9955bd1e995;
                    hash ^= hash >> 47u;
                }
            }
        } else if(*f=='i') {
            int i = va_arg(va, int);
            for(size_t p=0;p<sizeof(int);p++) {
                hash ^= ((unsigned char *) (&i))[p];
                hash *= 0x5bd1e9955bd1e995;
                hash ^= hash >> 47u;
            }
        }
    }
    return hash;
}

static inline __attribute__((unused))
uint64_t phash(uint64_t opt_hash,const char *format,...) {
    va_list va;
    va_start(va,format);
    uint64_t ret = phashv(opt_hash,format,va);
    va_end(va);
    return ret;
}

#endif
