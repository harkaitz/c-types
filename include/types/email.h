#ifndef TYPES_EMAIL_H
#define TYPES_EMAIL_H

#include <string.h>
#include <stdbool.h>

#define EMAIL_LENGTH_LIMIT 255

typedef struct email email;
struct email { char s[EMAIL_LENGTH_LIMIT+1]; };

static __attribute__((unused)) bool
email_is_valid_str (const char _s[], const char **_opt_reason) {
    int         user    = 0;
    int         arrobas = 0;
    int         domain  = 0;
    char        c       = '\0';
    size_t      i       = 0;
    if (!_s) goto fail_null_email;
    for (i=0,c=_s[i];c;c=_s[++i]) {
        if (i == EMAIL_LENGTH_LIMIT) {
            goto fail_too_long;
        } if (c == '@') {
            arrobas++;
        } else if ((c >= '0' && c<= '9' )   ||
                   (c >= 'A' && c<= 'Z' )   ||
                   (c >= 'a' && c<= 'z' )   ||
                   (c == '-')                ||
                   (c == '_')                ||
                   (c == '.')) {
            if (arrobas) domain++; else user++;
        } else {
            goto fail_invalid_character;
        }
    }
    if (arrobas != 1) goto fail_invalid_arroba_count;
    if (user < 3)     goto fail_invalid_user;
    if (domain < 3)   goto fail_invalid_domain;
    return true;
 fail_invalid_arroba_count:
    if (_opt_reason) *_opt_reason = "Invalid arroba count";
    return false;
 fail_invalid_character:
    if (_opt_reason) *_opt_reason = "Invalid character";
    return false;
 fail_invalid_user:
    if (_opt_reason) *_opt_reason = "Invalid user";
    return false;
 fail_invalid_domain:
    if (_opt_reason) *_opt_reason = "Invalid domain";
    return false;
 fail_null_email:
    if (_opt_reason) *_opt_reason = "Null email";
    return false;
 fail_too_long:
    if (_opt_reason) *_opt_reason = "Too long";
    return false;
}

static __attribute__((unused)) bool
email_is_valid(const email *_e, const char **_opt_reason) {
    return email_is_valid_str((_e)?_e->s:NULL, _opt_reason);
}

static __attribute__((unused)) bool
email_parse (email *_e, const char _s[]) {
    if (!email_is_valid_str(_s, NULL)) return false;
    if (_e) strcpy(_e->s, _s);
    return true;
}

static __attribute__((unused)) void
email_copy(email *_t, const email *_f) {
    if (_t && _f) {
        strcpy(_t->s, _f->s);
    }
}

static __attribute__((unused)) const char *
email_str(const email *_e) {
    return (_e)?_e->s:"";
}

#endif
