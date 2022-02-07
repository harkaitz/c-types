#ifndef SYS_AUTHORIZATION_H
#define SYS_AUTHORIZATION_H

#include <uuid/uuid.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdio.h>

#define AUTHORIZATION_MAX_USERNAME 255

typedef struct pam_handle pam_handle_t;

struct authorization_s {
    char username[AUTHORIZATION_MAX_USERNAME+1];
};


__thread __attribute__((weak))
struct authorization_s g_authorization[1];

static inline
void authorization_close (void) {
    memset(g_authorization, 0, sizeof(g_authorization));
}

static inline
bool authorization_open(const char _username[]) {
    for (size_t i=0; _username[i]; i++) {
        if (strchr("/:\\\"'%$\n\r \t", _username[i])) {
            syslog(LOG_ERR, "%s: Invalid username.", _username);
            return false;
        } else if (i>AUTHORIZATION_MAX_USERNAME) {
            syslog(LOG_ERR, "%s: Invalid username.", _username);
            return false;
        }
    }
    strcpy(g_authorization->username, _username);
    return true;
}

static inline
bool authorization_open_pam(pam_handle_t *_pam) {
    int pam_get_item(const pam_handle_t *pamh, int item_type, const void **item);
    const void *v;
    int res = pam_get_item(_pam, 2 /*PAM_USER*/, (const void **)&v);
    if (res!=0/*PAM_SUCCESS*/) {
        syslog(LOG_ERR, "Can't get username from PAM handle.");
        return false;
    }
    return authorization_open(v);
}

static inline
const char *authorization_get_username(void) {
    if (g_authorization->username[0]) {
        return g_authorization->username;
    } else {
        return NULL;
    }
}

#endif
