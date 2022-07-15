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

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

