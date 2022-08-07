#define _POSIX_C_SOURCE 201000L
#include <stdint.h>
#include <locale.h>
#include "../types/time_ss.h"

int main (int _argc, const char *_argv[]) {
    time_ss        t_ss;
    const char    *reason;
    if (_argc > 1 && (!strcmp(_argv[1], "-h") || !strcmp(_argv[1], "--help"))) {
        printf("Usage: sdate [@SECS|YYYY-MM-DD]\n");
        return 1;
    }

    setlocale(LC_ALL, "");
    setlocale(LC_TIME, ""); /* LC_ALL Doesn't set time. */
    
    if (_argc == 1) {
        printf("%s\n", time_day_str(time(NULL), &t_ss));
    } else if (_argv[1][0] == '@') {
        time_t t = strtoll(_argv[1]+1, NULL, 10);
        printf("%s\n", time_day_str(t, &t_ss));
    } else {
        time_t t = {0};
        if (!time_day_parse(&t, _argv[1], &reason)) {
            fprintf(stderr, "%s\n", reason);
            return 1;
        }
        printf("%jd\n", (intmax_t)t);
    }
    return 0;
}
