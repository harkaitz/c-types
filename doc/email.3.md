# NAME

struct email, email_is_valid(), email_parse(), email_copy(), email_str()

# SYNOPSIS

    #include <types/email.h>
    
    #define EMAIL_LENGTH_LIMIT 255
    typedef struct email email;
    struct email { char s[EMAIL_LENGTH_LIMIT+1]; };
    
    bool email_is_valid_str (const char _s[], const char **_opt_reason);
    bool email_is_valid     (const email *_e, const char **_opt_reason);
    bool email_parse        (email *_e, const char _s[]);
    void email_copy         (email *_t, const email *_f);
    cstr email_str          (const email *_e)
    
# DESCRIPTION

The mail type is defined as an struct for security, all this functions
can take a NULL argument.

# COLLABORATING

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

