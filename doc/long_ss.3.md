# NAME

long_parse(), ulong_parse(), long_str(), ulong_str()

# SYNOPSIS

    #include <types/long_ss.h>
    
    typedef struct long_ss {
        char s[64];
    } long_ss;

    typedef enum long_err_e {
        LONG_ERR_NULL_VALUE     = 0,
        LONG_ERR_INVALID_NUMBER = 1,
        LONG_ERR_OUT_OF_BOUNDS  = 2,
        LONG_ERR_MAX            = 3
    } long_err_e;
    
    bool long_parse  (long          *_out, const char *_s, long_err_e *_opt_reason);
    bool ulong_parse (unsigned long *_out, const char *_s, long_err_e *_opt_reason);
    
    const char *long_str  (long _n, long_ss *_ss);
    const char *ulong_str (unsigned long _n, long_ss *_ss);

# DESCRIPTION

This functions help parsing/unparsing numbers.

# COLLABORATING

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)
