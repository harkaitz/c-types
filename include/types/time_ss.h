#ifndef TYPES_TIME_H
#define TYPES_TIME_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef STATIC
#  define STATIC static __attribute__((unused))
#endif

typedef struct time_ss {
    char s[32];
} time_ss;

typedef enum time_day_err_e {
    TIME_DAY_ERR_NULL_VALUE    = 0,
    TIME_DAY_ERR_MISSING_YEAR  = 1,
    TIME_DAY_ERR_MISSING_MONTH = 2,
    TIME_DAY_ERR_MISSING_DAY   = 3,
    TIME_DAY_ERR_INVALID_YEAR  = 4,
    TIME_DAY_ERR_INVALID_MONTH = 5,
    TIME_DAY_ERR_INVALID_DAY   = 6,
    TIME_DAY_ERR_MAX           = 7
} time_day_err_e;

STATIC int
time_day_printf(char *b, size_t bsz, time_t _t) {
    struct tm *tm = localtime(&_t);
    return snprintf(b, bsz, "%04i-%02i-%02i", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);
}

STATIC const char *
time_day_str(time_t _t, time_ss *_ts) {
    time_day_printf(_ts->s, sizeof(_ts->s)-1, _t);
    return _ts->s;
}

STATIC bool
time_day_parse(time_t *_t, const char _s[], time_day_err_e *_opt_reason) {
    if (!_s) {
        if (_opt_reason) *_opt_reason = TIME_DAY_ERR_NULL_VALUE;
        return false;
    }
    time_day_err_e reason;
    char s[strlen(_s)+1]; strcpy(s, _s);
    char *_;
    char *s_y = strtok_r(s, "-/"    , &_);
    char *s_m = strtok_r(0, "-/"    , &_);
    char *s_d = strtok_r(0, "-/\n\r", &_);
    if (!s_y) { reason = TIME_DAY_ERR_MISSING_YEAR;  goto fail; }
    if (!s_m) { reason = TIME_DAY_ERR_MISSING_MONTH; goto fail; }
    if (!s_d) { reason = TIME_DAY_ERR_MISSING_DAY;   goto fail; }
    long y = strtol(s_y, NULL, 10);
    long m = strtol(s_m, NULL, 10);
    long d = strtol(s_d, NULL, 10);
    if (y<2000      ) { reason = TIME_DAY_ERR_INVALID_YEAR;  goto fail; }
    if (m<=0 || m>12) { reason = TIME_DAY_ERR_INVALID_MONTH; goto fail; }
    if (d<=0 || d>31) { reason = TIME_DAY_ERR_INVALID_DAY;   goto fail; }
    struct tm t = {0};
    t.tm_mday = d;
    t.tm_mon  = m;
    t.tm_year = y-1900;
    *_t = mktime(&t);
    return true;
 fail:
    if (_opt_reason) *_opt_reason = reason;
    return false;
}

#endif
