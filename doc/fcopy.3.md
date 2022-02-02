# FCOPY

fcopy_ff(), fcopy_fd()

# SYNOPSIS

    #include <io/fcopy.h>
    
    ssize_t fcopy_ff(FILE *_to, FILE *_fr, size_t _bsize, FILE *_opt_dots);
    ssize_t fcopy_fd(FILE *_to, int _fr, size_t _bsize, FILE *_opt_dots)

# DESCRIPTION

This functions read from one file descriptor or file pointer and write to
another. If you specify *_opt_dots* then dots are printed to *_opt_dots* in
the process for each write.

# RETURN VALUE

In case of error they return the written bytes in negative. In case of success
then it prints a positive value (or zero).

# COLLABORATING

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

# SEE ALSO

**open(3)**, **fopen(3)**, **open_memstream(3)**
