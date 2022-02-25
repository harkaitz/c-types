NAME
====

struct password, password_is_valid_str(), password_is_valid(), password_parse(),
password_str(), password_matches(), password_copy()

SYNOPSIS
========

    #include <types/password.h>
    
    #define PASSWORD_LENGTH_LIMIT   64
    #define PASSWORD_LENGTH_MINIMUM 8
    
    bool password_is_valid_str(const char _s[], const char **_opt_reason);
    bool password_is_valid(password *_p, const char **_opt_reason);
    
    bool password_parse (password *_p, const char _t[]);
    cstr password_str   (password *_p);
    bool password_matches(const password *_p1, const password *_p2);
    void password_copy(password *_t, const password *_f);

DESCRIPTION
===========

The password type is defined as an struct for security, all this functions
can take a NULL argument.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

