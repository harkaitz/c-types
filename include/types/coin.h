#ifndef TYPES_COIN_H
#define TYPES_COIN_H

#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef WEAK
#  define WEAK __attribute__((weak))
#endif
#ifndef STATIC
#  define STATIC static __attribute__((unused))
#endif


typedef struct coin_s {
    unsigned long cents;
    char          currency[8];
} coin_t;
typedef struct coin_ss {
    char s[64];
} coin_ss;

typedef enum coin_err_e {
    COIN_ERR_NO_DIGITS          =  0,
    COIN_ERR_OUT_OF_BOUNDS      =  1,
    COIN_ERR_NO_DECIMALS        =  2,
    COIN_ERR_INVALID_PRECISSION =  3,
    COIN_ERR_DUPLICATE_CURRENCY =  4,
    COIN_ERR_INVALID_CURRENCY   =  5,
    COIN_ERR_DIVISION_BY_ZERO   =  6,
    COIN_ERR_NOT_DIVISIBLE      =  7,
    COIN_ERR_NOT_SAME_CURRENCY  =  8,
    COIN_ERR_PASS_TO_NEGATIVE   =  9,
    COIN_ERR_MAX                = 10
} coin_err_e;

WEAK const char *g_coin_default = "eur";

STATIC coin_t
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
STATIC bool
coin_same_currency (coin_t _c1, coin_t _c2) {
    return (!strcasecmp(_c1.currency, _c2.currency));
}
STATIC bool
coin_equal (coin_t _c1, coin_t _c2) {
    if (_c1.cents != _c2.cents) return false;
    if (!coin_same_currency(_c1, _c2)) return false;
    return true;
}
STATIC bool
coin_parse (coin_t *_opt_out, const char _value[], coin_err_e *_opt_reason) {

    const char  *p            = _value;
    const char  *currency     = NULL;
    size_t       currency_len = 0;
    long         n1            = 0;
    long         n2            = 0;
    char        *next;

    /* Get currency from the start. */
    if (!isdigit(*p)) {
        currency = _value;
        while (!isdigit(*p)) ++p;
    }
    if (!isdigit(*p)) {
        goto fail_no_digits;
    }
    if (currency) {
        currency_len = p-currency;
    }
    
    /* Get first number. */
    n1 = strtol(p, &next, 10);
    if (next == p) {
        goto fail_no_digits;
    } else if (n1 >= LONG_MAX/200 || n2 < 0) {
        goto fail_out_of_bounds;
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
        if (*next != '\0') {
            goto fail_no_decimals;
        } else if (n2 < 0 || n2 >= 100) {
            goto fail_invalid_precission;
        }
        p = next;
    }

    /* Get currency from the end. */
    if (*p) {
        if (currency) {
            goto fail_dupplicate_currency;
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
    if (currency_len >= sizeof(_opt_out->currency)) {
        goto fail_invalid_currency;
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
 fail_no_digits:
    if (_opt_reason) *_opt_reason = COIN_ERR_NO_DIGITS;
    return false;
 fail_out_of_bounds:
    if (_opt_reason) *_opt_reason = COIN_ERR_OUT_OF_BOUNDS;
    return false;
 fail_no_decimals:
    if (_opt_reason) *_opt_reason = COIN_ERR_NO_DECIMALS;
    return false;
 fail_invalid_precission:
    if (_opt_reason) *_opt_reason = COIN_ERR_INVALID_PRECISSION;
    return false;
 fail_dupplicate_currency:
    if (_opt_reason) *_opt_reason = COIN_ERR_DUPLICATE_CURRENCY;
    return false;
 fail_invalid_currency:
    if (_opt_reason) *_opt_reason = COIN_ERR_INVALID_CURRENCY;
    return false;
}
STATIC int
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
STATIC bool
coin_divide1 (coin_t *_o, coin_t _i, unsigned long _div, coin_err_e *_opt_reason) {
    if (_div == 0) goto fail_division_by_zero;
    if (_i.cents % _div) goto fail_not_divisible;
    _o->cents = _i.cents / _div;
    strcpy(_o->currency,_i.currency);
    return true;
 fail_division_by_zero:
    if (_opt_reason) *_opt_reason = COIN_ERR_DIVISION_BY_ZERO;
    return false;
 fail_not_divisible:
    if (_opt_reason) *_opt_reason = COIN_ERR_NOT_DIVISIBLE;
    return false;
}
STATIC bool
coin_divide2 (long *_o, coin_t _i, coin_t _div, coin_err_e *_opt_reason) {
    if (!coin_same_currency(_i,_div)) goto fail_not_same_currency;
    if (_div.cents == 0) goto fail_division_by_zero;
    if (_i.cents % _div.cents) goto fail_not_divisible;    
    *_o = _i.cents / _div.cents;
    return true;
 fail_division_by_zero:
    if (_opt_reason) *_opt_reason = COIN_ERR_DIVISION_BY_ZERO;
    return false;
 fail_not_divisible:
    if (_opt_reason) *_opt_reason = COIN_ERR_NOT_DIVISIBLE;
    return false;
 fail_not_same_currency:
    if (_opt_reason) *_opt_reason = COIN_ERR_NOT_SAME_CURRENCY;
    return false;
}
STATIC bool
coin_substract (coin_t *_o, coin_t _c1, coin_t _c2, coin_err_e *_opt_reason) {
    if (!coin_same_currency(_c1,_c2)) goto fail_not_same_currency;
    if (_c2.cents > _c1.cents) goto fail_pass_to_negative; 
    _o->cents = _c1.cents - _c2.cents;
    strcpy(_o->currency,_c1.currency);
    return true;
 fail_not_same_currency:
    if (_opt_reason) *_opt_reason = COIN_ERR_NOT_SAME_CURRENCY;
    return false;
 fail_pass_to_negative:
    if (_opt_reason) *_opt_reason = COIN_ERR_PASS_TO_NEGATIVE;
    return false;
}
STATIC coin_t
coin_sum (coin_t _c1, coin_t _c2) {
    coin_t out;
    out.cents = _c1.cents + _c2.cents;
    strcpy(out.currency,_c1.currency);
    return out;
}
STATIC coin_t
coin_multiply (coin_t _c1, long _count) {
    coin_t out;
    out.cents = _c1.cents * _count;
    strcpy(out.currency,_c1.currency);
    return out;
}
STATIC const char *
coin_str(coin_t _c, coin_ss *_cs) {
    coin_sprintf(_c, sizeof(_cs->s), _cs->s);
    _cs->s[sizeof(_cs->s)-1] = '\0';
    return _cs->s;
}

#endif
