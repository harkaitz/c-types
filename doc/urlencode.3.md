# URLENCODE

urlencode(), urlencode_bv(), urlencode_fv(), urlencode_b(), urlencode_f(),
urlencode_post_f()

# SYNOPSIS

    #include <str/urlencode.h>
    
    /* Raw encoders. */
    int urlencode   (char _o[], size_t _osz, const char *_s);
    int urlencode_f (FILE *_fp, const char _s[]);
    
    /* Encode with printf expansion. (Uses the stack) */
    int urlencode_fmt_sv (char _o[], size_t _osz, const char *_fmt, va_list _va);
    int urlencode_fmt_s  (char _o[], size_t _osz, const char *_fmt, ...);
    int urlencode_fmt_fv (FILE *_fp, const char *_fmt, va_list _va);
    int urlencode_fmt_f  (FILE *_fp, const char *_fmt, ...);
    
    /* Prepare a post. */
    int urlencode_post_f(FILE *_fp, const char *_fmt, ...);

# DESCRIPTION

This functions are used to encode strings to URL encoding. The buffer variants
only fail if there's no enough memory in the stack (see *alloca(3)*). The file
pointer variants return -1 in case of output error.

# COLLABORATING

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

# SEE ALSO

**OPEN_MEMSTREAM(3)**, **ALLOCA(3)**

