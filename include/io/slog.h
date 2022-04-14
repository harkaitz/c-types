#ifndef SLOG_H
#define SLOG_H

#include <syslog.h>
#ifndef SLOG_PREFIX
#  define SLOG_PREFIX ""
#endif
#ifdef RELEASE
#  ifndef error
#    define error(FMT,...) syslog(LOG_ERR, SLOG_PREFIX FMT, ##__VA_ARGS__)
#  endif
#  ifndef info
#    define info(FMT,...) syslog(LOG_ERR, SLOG_PREFIX FMT, ##__VA_ARGS__)
#  endif
#  define debug(FMT,...) ({})
#else
#  ifndef error
#    define error(FMT,...) syslog(LOG_ERR, SLOG_PREFIX "%s: " FMT, __func__, ##__VA_ARGS__)
#  endif
#  ifndef info
#    define info(FMT,...) syslog(LOG_ERR, SLOG_PREFIX "%s: " FMT, __func__, ##__VA_ARGS__)
#  endif
#  ifndef debug
#    define debug(FMT,...) syslog(LOG_DEBUG, SLOG_PREFIX FMT, ##__VA_ARGS__)
#  endif
#endif

#ifdef _
#  define SLOG_T(T) _(T)
#else
#  define SLOG_T(T) T
#endif

#ifndef error_reason
#define error_reason(REASONP, MSG) ({           \
            if ((REASONP)) {                    \
                *(REASONP) = SLOG_T(MSG);       \
            } else {                            \
                error("%s", (MSG));             \
            }                                   \
        })
#endif

#ifndef error_fp
#  define error_fp(FP,FMT,...) fprintf(FP,FMT "\n", ##__VA_ARGS__)
#endif



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
