# NAME

bool_parse(), bool_str()

# SYNOPSIS

    #include <types/bool_ss.h>
    
    __attribute__((weak))
    const char *g_true_values[] = {
        "true","t","y","yes",NULL
    };
    __attribute__((weak))
    const char *g_false_values[] = {
        "false", "f", "n", "no",NULL
    };
    
    bool  bool_parse (bool *_opt_out, const char *_in, bool_err_e *_opt_reason);
    cstr *bool_str   (bool _in);

# DESCRIPTION

A secure form of parsing "true"/"false" string values.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

