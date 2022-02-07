#ifndef TYPES_KCGI_VALIDATORS_1_H
#define TYPES_KCGI_VALIDATORS_1_H

#include "bool_ss.h"
#include "uuid_ss.h"
#include "email.h"
#include "coin.h"
#include <sys/types.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <errno.h>
#include <syslog.h>
#include <assert.h>
#include <kcgi.h>

static __attribute__((unused))
int kvalid_uuid(struct kpair *_k) {
    uuid_t u;
    if (!kvalid_stringne(_k)) return 0;
    if (uuid_parse(_k->parsed.s, u)==-1) return 0;
    return 1;
}

static __attribute__((unused))
int kvalid_coin(struct kpair *_k) {
    coin_t c;
    if (!kvalid_stringne(_k)) return 0;
    if (!coin_parse(&c, _k->parsed.s, NULL)) return 0;
    return 1;
}

static __attribute__((unused))
bool khttp_get_bool(struct kreq *_k, bool *_o, int _key, bool _is_cookie) {
    bool_err_e     e = 0;
    int            r = 0;
    struct kpair **a = (_is_cookie)?_k->cookiemap:_k->fieldmap;
    struct kpair  *v = a[_key];
    if (!v/*err*/) goto fail_verification;
    switch (v->type) {
    case KPAIR_INTEGER:
        *_o = v->parsed.i;
        break;
    case KPAIR_DOUBLE:
        *_o = (v->parsed.d!=0)?true:false;
        break;
    case KPAIR_STRING:
        r = bool_parse(_o, v->parsed.s, &e);
        if (!r/*err*/) goto fail_invalid_value;
        break;
    default:
        goto fail_invalid_validator;
    }
    return true;
 fail_verification:
    syslog(LOG_ERR, "Key %s: Verification failed.", _k->keys[_key].name);
    return false;
 fail_invalid_value:
    syslog(LOG_ERR, "Key %s: Invalid value.", _k->keys[_key].name);
    return false;
 fail_invalid_validator:
    syslog(LOG_ERR, "Key %s: Invalid validator.", _k->keys[_key].name);
    abort();
}

static __attribute__((unused))
bool khttp_get_uuid(struct kreq *_k, uuid_t uuid, int _key, bool _is_cookie) {
    struct kpair **a = (_is_cookie)?_k->cookiemap:_k->fieldmap;
    struct kpair  *v = a[_key];
    if (!v/*err*/) goto fail_verification;
    if (_k->keys[_key].valid != kvalid_uuid/*err*/) goto fail_invalid_validator;
    uuid_parse(v->parsed.s, uuid);
    return true;
 fail_verification:
    syslog(LOG_ERR, "Key %s: Verification failed.", _k->keys[_key].name);
    return false;
 fail_invalid_validator:
    syslog(LOG_ERR, "Key %s: Invalid validator.", _k->keys[_key].name);
    abort();
}

static __attribute__((unused))
bool khttp_get_email(struct kreq *_k, email *email, int _key, bool _is_cookie) {
    struct kpair **a = (_is_cookie)?_k->cookiemap:_k->fieldmap;
    struct kpair  *v = a[_key];
    if (!v/*err*/) goto fail_verification;
    if (_k->keys[_key].valid != kvalid_email/*err*/) goto fail_invalid_validator;
    email_parse(email, v->parsed.s);
    return true;
 fail_verification:
    syslog(LOG_ERR, "Key %s: Verification failed.", _k->keys[_key].name);
    return false;
 fail_invalid_validator:
    syslog(LOG_ERR, "Key %s: Invalid validator.", _k->keys[_key].name);
    abort();
}

static __attribute__((unused))
bool khttp_get_coin(struct kreq *_k, coin_t *_c, int _key, const char *_dcur, bool _is_cookie) {
    struct kpair **a = (_is_cookie)?_k->cookiemap:_k->fieldmap;
    struct kpair  *v = a[_key];
    if (!v/*err*/) goto fail_verification;
    if (_k->keys[_key].valid != kvalid_coin/*err*/) goto fail_invalid_validator;
    coin_parse(_c, v->parsed.s, NULL);
 fail_verification:
    syslog(LOG_ERR, "Key %s: Verification failed.", _k->keys[_key].name);
    return false;
 fail_invalid_validator:
    syslog(LOG_ERR, "Key %s: Invalid validator.", _k->keys[_key].name);
    abort();
}

static __attribute__((unused))
bool khttp_get_ulong(struct kreq *_k, unsigned long *_n, int _key, bool _is_cookie) {
    struct kpair **a = (_is_cookie)?_k->cookiemap:_k->fieldmap;
    struct kpair  *v = a[_key];
    if (!v/*err*/) goto fail_verification;
    if (_k->keys[_key].valid != kvalid_coin/*err*/) goto fail_invalid_validator;
    *_n = v->parsed.i;
 fail_verification:
    syslog(LOG_ERR, "Key %s: Verification failed.", _k->keys[_key].name);
    return false;
 fail_invalid_validator:
    syslog(LOG_ERR, "Key %s: Invalid validator.", _k->keys[_key].name);
    abort();
}

static __attribute__((unused))
bool khttp_get_date(struct kreq *_k, time_t *_t, int _key, bool _is_cookie) {
    struct kpair **a = (_is_cookie)?_k->cookiemap:_k->fieldmap;
    struct kpair  *v = a[_key];
    if (!v/*err*/) goto fail_verification;
    if (_k->keys[_key].valid != kvalid_date/*err*/) goto fail_invalid_validator;
    *_t = v->parsed.i;
 fail_verification:
    syslog(LOG_ERR, "Key %s: Verification failed.", _k->keys[_key].name);
    return false;
 fail_invalid_validator:
    syslog(LOG_ERR, "Key %s: Invalid validator.", _k->keys[_key].name);
    abort();
}

static __attribute__((unused))
bool khttp_get_string(struct kreq *_k, const char **_s, int _key, bool _is_cookie) {
    struct kpair **a = (_is_cookie)?_k->cookiemap:_k->fieldmap;
    struct kpair  *v = a[_key];
    if (!v/*err*/) goto fail_verification;
    if (v->type != KPAIR_STRING/*err*/) goto fail_invalid_validator;
    *_s = v->parsed.s;
    return true;
 fail_verification:
    syslog(LOG_ERR, "Key %s: Verification failed.", _k->keys[_key].name);
    return false;
 fail_invalid_validator:
    syslog(LOG_ERR, "Key %s: Invalid validator.", _k->keys[_key].name);
    abort();
}

static __attribute__((unused))
bool khttp_get_strcpy(struct kreq *_k, size_t _sz, char _s[_sz], int _key, bool _is_cookie) {
    const char *ss;
    if (!khttp_get_string(_k, &ss, _key, _is_cookie)) return false;
    strncpy(_s, ss, _sz-1);
    _s[_sz-1] = '\0';
    return true;
}

static __attribute__((unused))
void khttp_head_del_cookie(struct kreq *_k, const char _n[]) {
    char  b[1024];
    char *t = khttp_epoch2str(0, b, sizeof(b)-1);
    khttp_head(_k, kresps[KRESP_SET_COOKIE], "%s=; Path=/; expires=%s", _n, t);
}

static __attribute__((unused))
void khttp_head_set_cookie(struct kreq *_k, const char _n[], const char _v[]) {
    khttp_head(_k, kresps[KRESP_SET_COOKIE], "%s=%s; Path=/", _n, _v);
}

#endif
