# NAME

str2num()

# SYNOPSIS

    #include <str/str2num.h>
    int str2num(const char *s1, int (*f) (const char *,const char *), ...);

# DESCRIPTION

The C standard doesn't define a mechanism to build switch statements out of
strings. Long if/strcmp structures can be complecated to read. This function
solves this issue.

    #include <str/str2num.h>
    
    switch(str2num(s, strcasecmp, "opt1", 1, "opt2", 2, NULL)) {
    case 1: ... break;
    case 2: ... break;
    default: ... break;
    }

# RETURN VALUE

If not found it returns -1.

# COLLABORATING

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

# SEE ALSO

**STRCMP(3)**, **STRCASECMP(3)**
