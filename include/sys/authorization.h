#ifndef SYS_AUTHORIZATION_H
#define SYS_AUTHORIZATION_H

#include "../io/slog.h"
#include "../types/username.h"
#include <uuid/uuid.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdio.h>

typedef struct pam_handle pam_handle_t;

__thread __attribute__((weak))
username g_authorization[1] = {0};

static inline void
authorization_close (void) {
    memset(g_authorization, 0, sizeof(g_authorization));
}

static inline bool
authorization_open(const char _username[]) {
    return username_parse(g_authorization, _username, NULL);
}

static inline bool
authorization_open_pam(pam_handle_t *_pam) {
    const void *v; int e;
    int pam_get_item(const pam_handle_t *pamh, int item_type, const void **item);
    e = pam_get_item(_pam, 2 /*PAM_USER*/, (const void **)&v);
    if (e!=0/*PAM_SUCCESS*/) {
        error("Can't get username from PAM handle.");
        return false;
    }
    return authorization_open(v);
}

static inline const char *
authorization_get_username(void) {
    return (g_authorization[0].s[0])?g_authorization[0].s:NULL;
}

#endif
