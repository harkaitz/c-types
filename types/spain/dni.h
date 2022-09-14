#ifndef _TYPES_SPAIN_DNI_H_
#define _TYPES_SPAIN_DNI_H_

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

typedef struct dni_s {
    long num;
    char chr;
    bool valid;
} dni_t;

static
char const DNI_CHARS[] = "TRWAGMYFPDXBNJZSQVHLCKE";

static inline bool
dni_parse(dni_t *_dni, char const *_s)
{
    bool e;
    char *ptr = NULL;
    
    _dni->num = strtol(_s, &ptr, 10);
    e = _dni->num > 0 && _dni->num <= 99999999;
    if (!e/*err*/ || !ptr) return false;
    if (*ptr=='-') ptr++;
    if (*ptr=='\0'/*err*/) return false;

    _dni->chr = toupper(*ptr);

    e = _dni->chr == DNI_CHARS[_dni->num % 23];
    if (!e/*err*/) return false;

    _dni->valid = true;
    return true;
}

static inline void
dni_random(dni_t *_dni)
{
    _dni->num = (rand())%100000000;
    _dni->chr = DNI_CHARS[_dni->num % 23];
    _dni->valid = true;
}

static inline int
dni_fputs(dni_t _dni, FILE *_fp)
{
    if (_dni.valid) {
        return fprintf(_fp, "%08li%c", _dni.num, _dni.chr);
    } else {
        return fputs("", _fp);
    }
}


#endif
