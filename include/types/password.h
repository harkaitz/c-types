#ifndef TYPES_PASSWORD_H
#define TYPES_PASSWORD_H

#include <string.h>
#include <stdbool.h>

#define PASSWORD_LENGTH_LIMIT   64
#define PASSWORD_LENGTH_MINIMUM 8

typedef struct password password;
struct password { char s[PASSWORD_LENGTH_LIMIT+1]; };

static __attribute__((unused)) bool
password_is_valid_str(const char _s[], const char **_opt_reason) {
    size_t l;
    if (!_s) goto fail_null_password;
    l = strlen(_s);
    if (l>PASSWORD_LENGTH_LIMIT)   goto fail_too_long;
    if (l<PASSWORD_LENGTH_MINIMUM) goto fail_too_short;
    return true;
 fail_null_password:
    if (_opt_reason) *_opt_reason = "Null email";
    return false;
 fail_too_long:
    if (_opt_reason) *_opt_reason = "Too long";
    return false;
 fail_too_short:
    if (_opt_reason) *_opt_reason = "Too short";
    return false;
}

static __attribute__((unused)) bool
password_is_valid(password *_p, const char **_opt_reason) {
    return password_is_valid_str((_p)?_p->s:NULL, _opt_reason);
}

static __attribute__((unused)) bool
password_parse (password *_p, const char _t[]) {
    if (!password_is_valid(_p, NULL)) return false;
    strcpy(_p->s, _t);
    return true;
}

static __attribute__((unused)) const char *
password_str (password *_p) {
    return (_p)?_p->s:"";
}

static __attribute__((unused)) bool
password_matches(const password *_p1, const password *_p2) {
    return _p1 && _p2 && !strcmp(_p1->s, _p1->s);
}

static __attribute__((unused)) void
password_copy(password *_t, const password *_f) {
    if (_t) strcpy(_t->s, _f->s);
}

#endif
