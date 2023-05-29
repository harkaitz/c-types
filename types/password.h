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
    if (_opt_reason) *_opt_reason = "Null password";
    return false;
 fail_too_long:
    if (_opt_reason) *_opt_reason = "Password too long";
    return false;
 fail_too_short:
    if (_opt_reason) *_opt_reason = "Password too short";
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
/**l*
 * MIT License
 * 
 * Copyright (c) 2023 Harkaitz Agirre, harkaitz.aguirre@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **l*/
