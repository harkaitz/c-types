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

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**PAM_START(3)**, **PAM_AUTHENTICATE(3)**, **PAM_GET_USER(3)**

