#include "../include/io/mconfig.h"
#include <unistd.h>
#include <libgen.h>

#define COPYRIGHT_LINE \
    "Bug reports, feature requests to gemini|https://harkadev.com/oss" "\n" \
    "Copyright (c) 2022 Harkaitz Agirre, harkaitz.aguirre@gmail.com" "\n" \
    ""

const char *help =
    "Usage: %s [OPTIONS...] [VARIABLE[=DEFAULT]]"                                 "\n"
    ""                                                                            "\n"
    "Read configuration files with the `VARIABLE VALUE` format and `#` comments." "\n"
    "The first variable has priority. The order of arguments is important."       "\n"
    ""                                                                            "\n"
    "-f FILE    : Read configuration file if it exists."                          "\n"
    "-F FILE    : Read configuration file."                                       "\n"
    "-o VAR=VAL : Specify variable from command line."                            "\n"
    ""                                                                            "\n"
    COPYRIGHT_LINE;

int main (int argc, char *argv[]) {
    int       c,r,i;
    char     *var,*val;
    mconfig_t mconfig = MCONFIG_INITIALIZER();
    int       retval  = 1;

    argv[0] = basename(argv[0]);
    if (argc == 1 || !strcasecmp(argv[1], "-h") || !strcasecmp(argv[1], "--help")) {
        printf(help, argv[0]);
        return 0;
    }
    openlog(argv[0], LOG_PERROR, LOG_USER);
    
    while((c = getopt (argc, argv, "f:F:o:")) != -1) {
        switch (c) {
        case 'f':
            r = mconfig_load(&mconfig, optarg, true);
            if (!r/*err*/) goto cleanup;
            break;
        case 'F':
            r = mconfig_load(&mconfig, optarg, false);
            if (!r/*err*/) goto cleanup;
            break;
        case 'o':
            var = optarg;
            if ((val = strchr(var, '='))) {
                *(val++) = '\0';
            } else {
                val = "true";
            }
            r = mconfig_add(&mconfig, var, val, NULL);
            if (!r/*err*/) goto cleanup;
            break;
        case '?':
        default:
            return 1;
        }
    }
    if (optind < argc) {
        for (i=optind; i<argc; i++) {
            var = argv[optind];
            if ((val = strchr(var, '='))) {
                *(val++) = '\0';
            } else {
                val = "";
            }
            printf("%s\n", mconfig_get(&mconfig, var, val));
        }
    } else {
        for (i=0; i<mconfig.vsz; i+=2) {
            if (mconfig.v[i] && mconfig.v[i+1]) {
                printf("%-30s %s\n", mconfig.v[i], mconfig.v[i+1]);
            }
        }
    }
    retval = 0;
 cleanup:
    mconfig_cleanup(&mconfig);
    return retval;
}
