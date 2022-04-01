# NAME

phash, phashv

# SYNOPSIS

    #include <phash.h>
    uint64_t phashv(uint64_t opt_hash,const char *format,va_list va)
    uint64_t phash(uint64_t opt_hash,const char *format,...)

# DESCRIPTION

This functions return the MurmurHash64 hash of the arguments. The *format*
string describes how the arguments should be treated.

+ 's' : The arguments is a null terminated string.
+ 'b' : Two arguments. A `size_t` describing the size and `void *` describing
        am object of the given size.
+ 'i' : A `int` type.

# EXAMPLE

    uint64_t hash = phash(0,"ss","abc","def");
    hash = phash(hash,"i",23);
    hash = phash(hash,"b",sizeof(object),&object);

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

