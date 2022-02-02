#include "../include/sys/pathsearch.h"
#include <stdio.h>
#include <libgen.h>

int main (int _argc, char *_argv[]) {
    int   err = 0;
    char *ret = NULL;
    _argv[0] = basename(_argv[0]);
    if (_argc == 1 || !strcmp(_argv[1], "-h") || !strcmp(_argv[1], "--help")) {
        fprintf(stderr, "Usage: pathsearch NAME\n" );
        return 1;
    }
    openlog(_argv[0], LOG_PERROR, LOG_USER);
    err = pathsearch(getenv("PATH"), ':', _argv[1], &ret);
    if (!err/*err*/) return 1;
    printf("%s\n", ret);
    free(ret);
    return 0;
}
