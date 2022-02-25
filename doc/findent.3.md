# NAME

findent(), fprintf_i()

# SYNOPSIS

    #include <io/findent.h>
    
    void findent   (FILE *_fp, int _shift);
    int  fprintf_i (FILE *_fp, const char _fmt[], ...);

# DESCRIPTION

This header has some auxiliary functions for terminal input and output.

Both *findent()* and *fprintf_i()* are used to print indented output. You shall
not put a newline in *fprintf_i()*.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

