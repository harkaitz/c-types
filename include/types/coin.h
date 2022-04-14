#ifndef TYPES_COIN_H
#define TYPES_COIN_H

#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../io/slog.h"

typedef struct coin_s {
    unsigned long cents;
    char          currency[8];
} coin_t;
typedef struct coin_ss {
    char s[64];
} coin_ss;

#define COIN_SS_STORE alloca(sizeof(coin_ss))

__attribute__((weak)) const char *g_coin_default = "eur";

static inline coin_t
coin (unsigned long _cents, const char _currency[]) {
    coin_t out = {0};
    out.cents = _cents;
    if (_currency) {
        strncpy(out.currency, _currency, sizeof(out.currency)-1);
    } else {
        strncpy(out.currency, g_coin_default, sizeof(out.currency)-1);
    }
    return out;
}

static inline bool
coin_same_currency (coin_t _c1, coin_t _c2) {
    return (!strcasecmp(_c1.currency, _c2.currency));
}

static inline bool
coin_equal (coin_t _c1, coin_t _c2) {
    if (_c1.cents != _c2.cents) return false;
    if (!coin_same_currency(_c1, _c2)) return false;
    return true;
}

static inline bool
coin_parse (coin_t *_opt_out, const char _value[], const char **_reason) {

    const char  *p            = _value;
    const char  *currency     = NULL;
    size_t       currency_len = 0;
    long         n1           = 0;
    long         n2           = 0;
    char        *next;

    /* Get currency from the start. */
    if (!isdigit(*p)) {
        currency = _value;
        while (!isdigit(*p)) ++p;
    }
    if (!isdigit(*p)/*err*/) {
        error_reason(_reason, "No digits");
        return false;
    }
    if (currency) {
        currency_len = p-currency;
    }
    
    /* Get first number. */
    n1 = strtol(p, &next, 10);
    if (next == p/*err*/) {
        error_reason(_reason, "No digits");
        return false;
    }
    if (n1 >= LONG_MAX/200 || n2 < 0/*err*/) {
        error_reason(_reason, "Out of bounds");
        return false;
    }
    p = next;

    /* Get cents. */
    if (strchr(".,", *p)) {
        ++p;
        char pp[3]; int ppn = 0;
        if (isdigit(*p)) pp[ppn++] = *(p++);
        if (isdigit(*p)) pp[ppn++] = *(p++);
        pp[ppn] = '\0';
        n2 = strtol(pp, &next, 10);
        if (*next != '\0'/*err*/) {
            error_reason(_reason, "No decimals");
            return false;
        }
        if (n2 < 0 || n2 >= 100/*err*/) {
            error_reason(_reason, "Invalid precission");
            return false;
        }
        p = next;
    }

    /* Get currency from the end. */
    if (*p) {
        if (currency/*err*/) {
            error_reason(_reason, "Duplicate currency");
            return false;
        }
        currency     = p;
        currency_len = strlen(currency);
    }

    /* Set default currency. */
    if (currency == NULL) {
        currency     = g_coin_default;
        currency_len = strlen(g_coin_default);
    }

    /* Currency too long. */
    if (currency_len >= sizeof(_opt_out->currency)/*err*/) {
        error_reason(_reason, "Invalid currency");
        return false;
    }

    /* Set coin. */
    if (_opt_out) {
        _opt_out->cents = (n1*100)+n2;
        if (currency[0]=='-') {
            currency++;
        }
        if (!strcmp(currency,"€")) {
            strcpy(_opt_out->currency, "eur");
        } else if (!strcmp(currency,"$")) {
            strcpy(_opt_out->currency, "usd");
        } else {
            strcpy(_opt_out->currency, currency);
        }
    }
    return true;
}

static inline int
coin_sprintf (coin_t _c, size_t _max, char _buf[_max]) {
    int r=0;
    unsigned long n1 = _c.cents/100;
    unsigned long n2 = _c.cents%100;
    r += snprintf(_buf, _max, "%ld.%.2ld", n1, n2);
    if (!strcasecmp(_c.currency, "eur")) {
        r += snprintf(_buf+r, _max-r, "%s", "€");
    } else {
        r += snprintf(_buf+r, _max-r, "%s", _c.currency);
    }
    return r;
}

static inline bool
coin_divide1 (coin_t *_o, coin_t _i, unsigned long _div, const char **_reason) {
    if (_div == 0/*err*/) {
        error_reason(_reason, "Division by zero");
        return false;
    }
    if (_i.cents % _div/*err*/) {
        error_reason(_reason, "Not divisible");
        return false;
    }
    _o->cents = _i.cents / _div;
    strcpy(_o->currency,_i.currency);
    return true;
}

static inline bool
coin_divide2 (long *_o, coin_t _i, coin_t _div, const char **_reason) {
    if (!coin_same_currency(_i,_div)/*err*/) {
        error_reason(_reason, "Not same currency");
        return false;
    }
    if (_div.cents == 0/*err*/) {
        error_reason(_reason, "Division by zero");
        return false;
    }
    if (_i.cents % _div.cents/*err*/) {
        error_reason(_reason, "Not divisible");
        return false;
    }
    *_o = _i.cents / _div.cents;
    return true;
}

static inline bool
coin_substract (coin_t *_o, coin_t _c1, coin_t _c2, const char **_reason) {
    if (!coin_same_currency(_c1,_c2)/*err*/) {
        error_reason(_reason, "Not the same surrency");
        return false;
    }
    if (_c2.cents > _c1.cents/*err*/) {
        error_reason(_reason, "Pass to negative");
        return false;
    }
    _o->cents = _c1.cents - _c2.cents;
    strcpy(_o->currency,_c1.currency);
    return true;
}

static inline coin_t
coin_sum (coin_t _c1, coin_t _c2) {
    coin_t out;
    out.cents = _c1.cents + _c2.cents;
    strcpy(out.currency,_c1.currency);
    return out;
}

static inline coin_t
coin_multiply (coin_t _c1, long _count) {
    coin_t out;
    out.cents = _c1.cents * _count;
    strcpy(out.currency,_c1.currency);
    return out;
}

static inline const char *
coin_str(coin_t _c, coin_ss *_cs) {
    coin_sprintf(_c, sizeof(_cs->s), _cs->s);
    _cs->s[sizeof(_cs->s)-1] = '\0';
    return _cs->s;
}

#endif
