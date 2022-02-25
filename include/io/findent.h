#ifndef IO_FINDENT_H
#define IO_FINDENT_H

#include <stdio.h>
#include <stdarg.h>

#ifndef FINDENT_WEAK_THREAD
#  define FINDENT_WEAK_THREAD __attribute__((weak)) __thread
#endif
#ifndef FINDENT_WEAK
#  define FINDENT_WEAK __attribute__((weak))
#endif

FINDENT_WEAK_THREAD
struct {
    FILE  *fp;
    int    indent;
} __findent[10] = {0};


FINDENT_WEAK
void findent(FILE *_fp, int _shift) {
    for (int i=0; i<10; i++) {
        if (__findent[i].fp == _fp) {
            __findent[i].indent += _shift;
            break;
        }
        if (!__findent[i].fp) {
            __findent[i].fp      = _fp;
            __findent[i].indent += _shift;
            break;
        }
    }
}

FINDENT_WEAK
int fprintf_i(FILE *_fp, const char _fmt[], ...) {
    va_list va;
    int ret = 0,i,j,e;
    for (i=0; i<10; i++) {
        if (__findent[i].fp != _fp) continue;
        for (j=0; j<__findent[i].indent; j++) {
            e = fputs("    ", _fp);
            if (e == EOF/*err*/) return -1;
            ret += 4;
        }
        break;
    }
    va_start(va, _fmt);
    e = vfprintf(_fp, _fmt, va);
    va_end(va);
    if (e < 0/*err*/) return -1;
    ret += e;
    e = fputs("\n", _fp);
    if (e == EOF/*err*/) return -1;
    ret += 1;
    return ret;
}

#endif
/**l*
 * This software is free to use and modify.
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
