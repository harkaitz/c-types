# SYS-AUTHORIZATION

struct authorization_s, authorization_close(), authorization_open(),
authorization_open_pam(), authorization_get_username()

# SYNOPSIS

    #include <sys/authorization.h>
    
    void        authorization_close        (void);
    bool        authorization_open         (const char _username[]);
    bool        authorization_open_pam     (pam_handle_t *_pam);
    
    const char *authorization_get_username (void);

# DESCRIPTION

With functions *authorization_open* and *authorization_open_pam* authorize
a *thread* to work as *user*. The thread can check for authorization with
*authorization_get_username*.

For *authentication* (which is completetly different to *authorization*) check
out *pam_authenticate(3)*.

# RETURN VALUE

All return true for success false on failure. *authorization_get_username* returns
NULL when no authorization was set by any open.

# COLLABORATING

You can collaborate with this project either by making bug reports,
making pull requests or making a donation.

- Bug reports, pull requests: Harkaitz Agirre <harkaitz.aguirre@gmail.com>
- *Bitcoin* : _1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV_
- *Binance* : _bnb194ay2cy83jjp644hdz8vjgjxrj5nmmfkngfnul_
- *Monero* : _88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti_

# SEE ALSO

**PAM_START(3)**, **PAM_AUTHENTICATE(3)**, **PAM_GET_USER(3)**

