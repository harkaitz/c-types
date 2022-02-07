# NAME

streq2map(), strmap_get()

# SYNOPSIS

    #include <str/strarray.h>
    
    typedef int (*strcmp_f) (const char *s1, const char *s2);
    
    void  streq2map (char *_i[], int _o_sz, char *_o[_o_sz]);
    
    char *strmap_get(char *_a[], const char _key[], strcmp_f _cmp);

# DESCRIPTION

This are functions to handle *map string arrays* and *equal string arrays*.

    char *map[] = {"var1", "val1", "var2", "val2", NULL};
    char *eq[]  = {"var1=val1", "var2=val2", NULL};

The *map string arrays* are easier to forge programmaticaly whilst *equal
string arrays* are better for command line arguments. Use the first to
configure your libraries.

# RETURN VALUE

NULL when not found.

# COLLABORATING

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

# SEE ALSO

**STRCMP(3)**, **STRCASECMP(3)**
