# NAME

crest_destroy(), crest_create(), crest_set_auth(), crest_start_url_v(),
crest_start_url(), crest_post_data(), crest_perform(), crest_get_json()

# SYNOPSIS

    #include <curl/crest.h>
    
    typedef struct crest crest;
    typedef struct crest_result {
        const char *ctype;
        long        rcode;
        char       *d;
        size_t      dsz;
    } crest_result;
    
    bool crest_create  (crest **_o);
    void crest_destroy (crest *_r);
    
    bool crest_set_auth (crest *_o, const char _user[], const char _pass[]);
    
    bool crest_start_url_v (crest *_r, const char _fmt[], va_list _va);
    bool crest_start_url   (crest *_r, const char _fmt[], ...);
    
    bool crest_post_data (crest *_r, const char _ctype[], FILE **_o_wfp);
    
    bool crest_perform  (crest   *_r, const char **_ctype  , long *_rcode, char **_d,   size_t *_dsz);
    bool crest_get_json (json_t **_o, const char   _ctype[], long  _rcode, char   _d[], size_t  _dsz);

# DESCRIPTION

This functions help developing REST clients using CURL. You can create/destroy
a *crest structure* with *crest_create/crest_destroy*.

After creating you can configure shared options between requests with
*crest_set_auth*.

Start a request specifying the URL with *crest_start_url*. In order to include
content to the request use *crest_post_data*.

Finally perform a request with *crest_perform*. If the response is a JSON you
can parse it with *crest_get_json* (will use jansson).

# RETURN VALUE

Return *true* on success *false* in error.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**OPEN_MEMSTREAM(3)**, **JANSSON(3)**, **CURL(3)**
