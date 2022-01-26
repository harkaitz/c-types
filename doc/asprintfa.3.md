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

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

# SEE ALSO

**ALLOCA(3)**
