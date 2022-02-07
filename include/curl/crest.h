#ifndef CREST_H
#define CREST_H

#include "../str/str2num.h"
#include "../str/urlencode.h"
#include <curl/curl.h>
#include <jansson.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

typedef struct crest {
    CURL       *curl;
    FILE       *fp[3];
    char       *d[3];
    size_t      dsz[3];
    char       *userpwd_m;
    bool        verbose;
    bool        post;
    const char *post_ctype;
} crest;

typedef struct crest_result {
    const char *ctype;
    long        rcode;
    char       *d;
    size_t      dsz;
} crest_result;

#define CREST_CONTENT_TYPE_JSON "application/json"

static __attribute__((unused))
void crest_destroy(crest *_r) {
    if (_r) {
        if (_r->curl)  curl_easy_cleanup(_r->curl);
        if (_r->fp[0]) fclose(_r->fp[0]);
        if (_r->fp[1]) fclose(_r->fp[1]);
        if (_r->fp[2]) fclose(_r->fp[2]);
        free(_r->d[0]);
        free(_r->d[1]);
        free(_r->d[2]);
        free(_r->userpwd_m);
        free(_r);
    }
}

static __attribute__((unused))
bool crest_create(crest **_o) {
    crest *o = NULL;
    o = calloc(1, sizeof(struct crest));
    if (!o/*err*/) goto cleanup_errno;
    o->curl = curl_easy_init();
    if (!o->curl/*err*/) goto cleanup_curl_init;
    o->fp[0] = open_memstream(&(o->d[0]), &(o->dsz[0]));
    o->fp[2] = open_memstream(&(o->d[2]), &(o->dsz[2]));
    if (!o->fp[0] || !o->fp[2]/*err*/) goto cleanup_errno;
    *_o = o;
    return true;
 cleanup_errno:
    syslog(LOG_ERR, "%s", strerror(errno));
    goto cleanup;
 cleanup_curl_init:
    syslog(LOG_ERR, "Curl initialization failed.");
    goto cleanup;
 cleanup:
    crest_destroy(o);
    return false;
}

static __attribute__((unused))
bool crest_set_auth(crest *_o, const char _user[], const char _pass[]) {
    const char *user = (_user)?_user:"";
    const char *pass = (_pass)?_pass:"";
    size_t      upwd_l = strlen(user)+strlen(pass)+2;
    free(_o->userpwd_m);
    _o->userpwd_m = malloc(upwd_l);
    if (!_o->userpwd_m/*err*/) goto failure_errno;
    sprintf(_o->userpwd_m, "%s:%s", user, pass);
    return true;
 failure_errno:
    syslog(LOG_ERR, "%s", strerror(errno));
    return false;
}

static __attribute__((unused))
bool crest_start_url_v(crest *_r, const char _fmt[], va_list _va) {
    int  res;
    _r->post = false;
    if (_r->fp[1]) { fclose(_r->fp[1]); _r->fp[1] = NULL; }
    if (_r->d[1])  { free(_r->d[1]);    _r->d[1]  = NULL; } 
    
    /* Reset file pointers and forge url. */
    res =
        fseek(_r->fp[0], 0, SEEK_SET)!=-1 &&
        fseek(_r->fp[2], 0, SEEK_SET)!=-1 &&
        urlencode_post_fv(_r->fp[2], true, _fmt, _va)!=-1 &&
        fputc('\0', _r->fp[2])!=EOF &&
        fflush(_r->fp[2])!=EOF;
    /* Reset curl. */
    curl_easy_reset(_r->curl);
    /* Set URL. */
    if (_r->verbose) syslog(LOG_INFO, "crest: %s", _r->d[2]);
    res = curl_easy_setopt(_r->curl, CURLOPT_URL, _r->d[2]);
    if (res!=CURLE_OK/*err*/) goto fail_curl;
    /* Set options. */
    curl_easy_setopt(_r->curl, CURLOPT_SSL_VERIFYPEER , 0L);
    curl_easy_setopt(_r->curl, CURLOPT_SSL_VERIFYHOST , 0L);
    curl_easy_setopt(_r->curl, CURLOPT_LOW_SPEED_TIME , 30L);
    curl_easy_setopt(_r->curl, CURLOPT_LOW_SPEED_LIMIT, 10L);
    curl_easy_setopt(_r->curl, CURLOPT_ACCEPT_ENCODING, NULL);
    curl_easy_setopt(_r->curl, CURLOPT_VERBOSE        , 0L);
    if (_r->userpwd_m) {
        curl_easy_setopt(_r->curl, CURLOPT_USERPWD, _r->userpwd_m);
    }
    curl_easy_setopt(_r->curl, CURLOPT_WRITEFUNCTION, fwrite);
    curl_easy_setopt(_r->curl, CURLOPT_WRITEDATA, _r->fp[0]);
    return true;
 fail_curl:
    syslog(LOG_ERR, "%s", curl_easy_strerror(res));
    return false;
}

static __attribute__((unused))
bool crest_start_url(crest *_r, const char _fmt[], ...) {
    va_list va;
    va_start(va, _fmt);
    bool r = crest_start_url_v(_r, _fmt, va);
    va_end(va);
    return r;
}

static __attribute__((unused))
bool crest_post_data(crest *_r, const char _ctype[], FILE **_o_wfp) {
    _r->post       = true;
    _r->post_ctype = _ctype;
    if (_r->fp[1]) { fclose(_r->fp[1]); _r->fp[1] = NULL; }
    if (_r->d[1])  { free  (_r->d[1]);  _r->d[1]  = NULL; } 
    _r->fp[1] = open_memstream(&_r->d[1], &_r->dsz[1]);
    if (!_r->fp[1]/*err*/) goto cleanup_errno;
    *_o_wfp = _r->fp[1];
    return true;
 cleanup_errno:
    syslog(LOG_ERR, "%s", strerror(errno));
    return false;
}

static __attribute__((unused))
bool crest_perform(crest *_r, const char **_ctype, long *_rcode, char **_d, size_t *_dsz) {
    int                res;
    long               dsz;
    struct curl_slist *hs     = NULL;
    bool               retval = false;
    if (_r->post) {
        curl_easy_setopt(_r->curl, CURLOPT_POST, 1L);
    }
    if (_r->fp[1]) {
        curl_easy_setopt(_r->curl, CURLOPT_READFUNCTION, fread);
        curl_easy_setopt(_r->curl, CURLOPT_READDATA, _r->fp[1]);
        fseek(_r->fp[1], 0, SEEK_SET);
        if (_r->post_ctype) {
            char *b = alloca(1024);
            sprintf(b, "Content-Type: %s", _r->post_ctype);
            hs = curl_slist_append(hs, b);
            curl_easy_setopt(_r->curl, CURLOPT_HTTPHEADER, hs);
        }
    }
    
    res = curl_easy_perform(_r->curl);
    if (res!=CURLE_OK/*err*/) goto fail_curl;
    if (_ctype) {
        res = curl_easy_getinfo(_r->curl, CURLINFO_CONTENT_TYPE, _ctype);
        if (res!=CURLE_OK/*err*/) goto fail_curl;
    }
    if (_rcode) {
        res = curl_easy_getinfo(_r->curl, CURLINFO_RESPONSE_CODE, _rcode);
        if (res!=CURLE_OK/*err*/) goto fail_curl;
    }
    if (_dsz) {
        dsz = ftell(_r->fp[0]);
        if (dsz==-1/*err*/) goto fail_errno;
        *_dsz = dsz;
    }
    if (_d) {    
        res = fputc('\0', _r->fp[0])!=EOF && fflush(_r->fp[0])!=EOF;
        if (!res/*err*/) goto fail_errno;
        *_d = _r->d[0];
    }
    retval = true;
    goto cleanup;
 fail_curl:
    syslog(LOG_ERR, "%s", curl_easy_strerror(res));
    goto cleanup;
 fail_errno:
    syslog(LOG_ERR, "%s", strerror(errno));
    goto cleanup;
 cleanup:
    if (hs) curl_slist_free_all(hs);
    return retval;
}

static inline
bool crest_get_json(json_t **_o, const char _ctype[], long _rcode, char _d[], size_t _dsz) {
    bool          r = false;
    json_t       *o = NULL;
    json_t       *j;
    json_error_t  e = {0};
    if (strcmp(_ctype, CREST_CONTENT_TYPE_JSON)) {
        syslog(LOG_ERR, "The server didn't return a JSON.");
        goto cleanup;
    }
    o = json_loadb(_d, _dsz, JSON_ALLOW_NUL, &e);
    if (!o) {
        syslog(LOG_ERR, "Failed parsing response: %i:%s", e.line, e.text);
        goto cleanup;
    }
    if ((j = json_object_get(o, "error"))) {
        const char *c = json_string_value(json_object_get(j, "code"));
        const char *t = json_string_value(json_object_get(j, "type"));
        const char *m = json_string_value(json_object_get(j, "message"));
        syslog(LOG_ERR, "Failed, return code %li: %s: %s", _rcode,(c)?c:((t)?t:""),(m)?m:"");
        goto cleanup;
    }
    if (_rcode != 200) {
        syslog(LOG_ERR, "Failed, return code %li.", _rcode);
        goto cleanup;
    }
    *_o = json_incref(o);
    r = true;
 cleanup:
    json_decref(o);
    return r;
}





#endif
