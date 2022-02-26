#ifndef IO_PROMPT_H
#define IO_PROMPT_H

#include "fgetpw.h"
#include <string.h>

static inline
char *prompt_fgets (const char _prompt[], char _b[], size_t _blen) {
    if (isatty(0) && _prompt) {
        fputs(_prompt, stderr);
        fflush(stderr);
    }
    if (!fgets(_b, _blen, stdin)) {
        return NULL;
    }
    char *nl = memchr(_b, '\n', _blen);
    if (nl) *nl = '\0';
    return _b;
}

static inline
char *prompt_fgetpw (const char _prompt[], char _b[], size_t _blen) {
    if (isatty(0)) {
        if (_prompt) {
            fputs(_prompt, stderr);
            fflush(stderr);
        }
        if (!fgetpw(_b, _blen, stdin)) return NULL;
        if (_prompt) {
            fputs("\n", stderr);
        }
    } else {
        if (!fgets(_b, _blen, stdin)) return NULL;
    }
    char *nl = memchr(_b, '\n', _blen);
    if (nl) *nl = '\0';
    return _b;
}

#endif
/**l*
 * 
 * MIT License
 * 
 * Bug reports, feature requests to gemini|https://harkadev.com/oss
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
