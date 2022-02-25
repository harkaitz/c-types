#ifndef TYPES_UUID_SS_H
#define TYPES_UUID_SS_H

#include <uuid/uuid.h>
#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include <stdbool.h>

#define UUID_SS_LENGTH 36
#define UUID_SS_STORE alloca(UUID_SS_LENGTH+1)
#define UUID_STORE alloca(sizeof(uuid_t))

typedef struct uuid_ss uuid_ss;
struct uuid_ss { char s[UUID_SS_LENGTH+1]; };

static __attribute__((unused)) const char *
uuid_str(const uuid_t _uuid, uuid_ss *_uuid_ss) {
    const char *u_null = "00000000-0000-0000-0000-000000000000";
    if (_uuid && _uuid_ss) {
        uuid_unparse_lower(_uuid, _uuid_ss->s);
        return _uuid_ss->s;
    } else if (_uuid_ss) {
        strcpy(_uuid_ss->s, u_null);
        return _uuid_ss->s;
    } else {
        return u_null;
    }
}

static __attribute__((unused)) const char *
uuid_str_2(const char _prefix[], const uuid_t _uuid, size_t _bsz, char _b[]) {
    uuid_ss u;
    snprintf(_b, _bsz, "%s%s", _prefix, uuid_str(_uuid, &u));
    _b[_bsz-1] = '\0';
    return _b;
}

static __attribute__((unused)) bool
uuid_parse_nn(const char *_s, uuid_t _uuid) {
    if (uuid_parse(_s, _uuid)==-1) {
        syslog(LOG_ERR, "Invalid UUID: %s", _s);
        return false;
    } else if (uuid_is_null(_uuid)) {
        syslog(LOG_ERR, "Null UUID: %s", _s);
        return false;
    } else {
        return true;
    }
}


#endif
/**l*
 * 
 * This software is free to use and modify, but not free to maintain.
 * 
 * Donate bitcoin: 1C1ZzDje7vHhF23mxqfcACE8QD4nqxywiV
 * Donate monero: 88JP1c94kDEbyddN4NGU574vwXHB6r3FqcFX9twmxBkGNSnf64c5wjE89YaRVUk7vBbdnecWSXJmRhFWUcLcXUTFJVddZti
 * Copyright (c) 2022 Harkaitz Agirre, harkaitz.aguirre@gmail.com
 * 
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 **l*/
