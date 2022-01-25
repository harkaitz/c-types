#include "../include/types/email.h"
#include <libgen.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
    const char *reason;
    /* Print help. */
    argv[0] = basename(argv[0]);
    if (argc <= 1) {
        fprintf(stderr,"Usage: %s EMAIL\n", argv[0]);
        return 1;
    }
    /* Check the mail. */
    if (!email_is_valid_str(argv[1], &reason)) {
        fprintf(stderr, "%s\n", reason);
        return 1;
    }
    return 0;
}
