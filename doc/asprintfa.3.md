# NAME

asprintfa

# SYNOPSIS

    #include <str/asprintf.h>
    
    char *asprintfa(FMT, ...);
    char *vasprintfa(FMT, ...)

# DESCRIPTION

The arguments in (...) are evaluated twice, once for calculating the buffer size
the other to print to a buffer allocated in the stack with alloca.

There's no need to free the returned string, it has function life.

# RETURN VALUE

Always returns a string. No error detection.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**ALLOCA(3)**
