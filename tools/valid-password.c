#include "../include/types/password.h"
#include <stdio.h>
#include <string.h>
#include <libgen.h>

int main (int argc, char *argv[]) {
    const char *reason   = NULL;
    password    password = {0};
    argv[0] = basename(argv[0]);
    if (!fgets(password.s, sizeof(password.s)-1, stdin)) { return 1; }
    char *nl = strchr(password.s, '\n');
    if (!nl) {
        fprintf(stderr, "The password is too long.\n");
        return 1;
    }
    *nl = '\0';
    if (!password_is_valid(&password, &reason)) {
        fprintf(stderr, "%s\n", reason);
        return 1;
    }
    printf("%s\n", password_str(&password));
    return 0;
}
