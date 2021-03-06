#define _GNU_SOURCE
#include "../types/time_ss.h"

int main (int _argc, const char *_argv[]) {
    time_ss        t_ss;
    const char    *reason;
    if (_argc == 1 || !strcmp(_argv[1], "-h") || !strcmp(_argv[1], "--help")) {
        printf("Usage: sdate @SECS|YYYY-MM-DD\n");
        return 1;
    }
    if (_argv[1][0] == '@') {
        time_t t = strtol(_argv[1]+1, NULL, 10);
        printf("%s\n", time_day_str(t, &t_ss));
    } else {
        time_t t;
        if (!time_day_parse(&t, _argv[1], &reason)) {
            fprintf(stderr, "%s", reason);
            return 1;
        }
        printf("%li\n", t);
    }
    return 0;
}
