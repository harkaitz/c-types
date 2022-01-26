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

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

