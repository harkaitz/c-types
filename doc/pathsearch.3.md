# NAME

pathsearch()

# SYNOPSIS

    #include <sys/pathsearch.h>
    
    bool pathsearch(const char _path[],
                    char       _sep,
                    const char _name[],
                    char     **_o);

# DESCRIPTION

Search executable named *_name* in a directory list in *_path* separated by *_sep*. The
result is stored in *_o* and must be freed with *free()*. It returns *true* on
success and *false* in case of error.

# COLLABORATING

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

