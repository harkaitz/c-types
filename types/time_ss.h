#ifndef TYPES_TIME_H
#define TYPES_TIME_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

typedef struct time_ss {
    char s[32];
} time_ss;

#define TIME_SS_STORE alloca(sizeof(struct time_ss))
#define TIME_SS_FORMAT "%x"

extern char *strptime (const char *, const char *,struct tm *);

static inline int
time_day_printf(char *b, size_t bsz, time_t _t)
{
    struct tm *tm = localtime(&_t);
    return strftime(b, bsz, TIME_SS_FORMAT, tm);
}

static inline const char *
time_day_str(time_t _t, time_ss *_ts)
{
    time_day_printf(_ts->s, sizeof(_ts->s)-1, _t);
    return _ts->s;
}

static inline bool
time_day_parse(time_t *_t, const char _s[], const char **_reason)
{
    struct tm tm = {0};
    char *c = strptime(_s, TIME_SS_FORMAT, &tm);
    if (c && (*c=='\0' || strchr("\n \t", *c))) {
        *_t = mktime(&tm);
        return true;
    } else if (_reason) {
        *_reason = "Invalid time format.";
        return false;
    } else {
        return false;
    }
}

#endif
