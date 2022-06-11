#ifndef TYPES_TIME_H
#define TYPES_TIME_H

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <str/mtext.h>
#include "../io/slog.h"

typedef struct time_ss {
    char s[32];
} time_ss;

#define TIME_SS_STORE alloca(sizeof(struct time_ss))


static inline int
time_day_printf(char *b, size_t bsz, time_t _t) {
    struct tm *tm = localtime(&_t);
    //const char *lang = mtext_lang();
    //if (!strcasecmp(lang, "es")) {
    //    return snprintf(b, bsz, "%02i/%02i/%04i", tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900);
    //} else {
        return snprintf(b, bsz, "%04i/%02i/%02i", tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);
    //}
}

static inline const char *
time_day_str(time_t _t, time_ss *_ts) {
    time_day_printf(_ts->s, sizeof(_ts->s)-1, _t);
    return _ts->s;
}

static inline bool
time_day_parse(time_t *_t, const char _s[], const char **_reason) {
    if (!_s) {
        error_reason(_reason, NULL_STRING, "Null string");
        return false;
    }
    char s[64]; strncpy(s, _s, sizeof(s)); s[sizeof(s)-1]='\0';
    char *s_t;
    char *s_y = strtok_r(s, "-/"    , &s_t);
    char *s_m = strtok_r(0, "-/"    , &s_t);
    char *s_d = strtok_r(0, "-/\n\r", &s_t);
    if (!s_y) { error_reason(_reason, MISSING_YEAR, "Missing year, shall be YYYY-MM-DD");  return false; }
    if (!s_m) { error_reason(_reason, MISSING_MONTH, "Missing month, shall be YYYY-MM-DD"); return false; }
    if (!s_d) { error_reason(_reason, MISSING_DAY, "Missing day, shall be YYYY-MM-DD");   return false; }
    long y = strtol(s_y, NULL, 10);
    long m = strtol(s_m, NULL, 10);
    long d = strtol(s_d, NULL, 10);
    if (y<100) y+=2000;
    if (y<1979      ) { error_reason(_reason, INVALID_YEAR, "Invalid year");  return false; }
    if (m<=0 || m>12) { error_reason(_reason, INVALID_MONTH, "Invalid month"); return false; }
    if (d<=0 || d>31) { error_reason(_reason, INVALID_DAY, "Invalid day");   return false; }
    struct tm t = {0};
    t.tm_mday = d;
    t.tm_mon  = m;
    t.tm_year = y-1900;
    *_t = mktime(&t);
    return true;
}

#endif
