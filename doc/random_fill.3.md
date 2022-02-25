# NAME

random_fill(), ALPHABET, HEXADECIMAL

# SYNOPSIS

    #include <str/random_fill.h>

    char *random_fill(char *out, int len, const char *comp);

    #define ALPHABET    "abcdefghijklmnopqrstuvxyzABCDEFGHIJKLMNOPQRSTUVXYZ1234567890"
    #define HEXADECIMAL "0123456789abcdef"

# DESCRIPTION

Fill a string with random characters. A null character is inserted.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**RANDOM(2)**
