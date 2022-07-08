#ifndef SYS_AUTHORIZATION_H
#define SYS_AUTHORIZATION_H

#include "../types/username.h"
#include <uuid/uuid.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdio.h>

typedef struct pam_handle pam_handle_t;

__thread __attribute__((weak))
username g_authorization[1] = {0};

__thread __attribute__((weak))
bool     g_authorization_is_root = false;

__attribute__((weak))
const char *AUTHORIZATION_ROOT_USERNAME;

static inline void
authorization_close (void) {
    memset(g_authorization, 0, sizeof(g_authorization));
}

static inline bool
authorization_open(const char _username[]) {
    const char *reason;
    if (!username_parse(g_authorization, _username, &reason)) {
        g_authorization->s[0] = '\0';
        g_authorization_is_root = false;
        syslog(LOG_ERR, "%s", reason);
        return false;
    }
    g_authorization_is_root = 
        AUTHORIZATION_ROOT_USERNAME
        &&
        !strcmp(g_authorization->s, AUTHORIZATION_ROOT_USERNAME);
    return true;
}

static inline const char *
authorization_get_username(void) {
    return (g_authorization->s[0])?g_authorization->s:NULL;
}

static inline bool
authorization_user_is(const char _username[]) {
    if (g_authorization_is_root) {
        return true;
    } else if (!g_authorization->s[0]) {
        return false;
    } else if (!strcmp(g_authorization->s, _username)) {
        return true;
    } else {
        return false;
    }
}

static inline bool
authorization_user_is_root(void) {
    return g_authorization_is_root;
}



#endif
