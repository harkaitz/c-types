#ifndef SECURITY_PAM_AUTO_H
#define SECURITY_PAM_AUTO_H

#include <security/pam_appl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <syslog.h>
#include <str/mtext.h>


typedef struct pam_auto {
    const char *username;
    const char *password;
    FILE       *fp;
} pam_auto;



int __attribute__((weak))
pam_weblogin_conv(int                        _msgsz,
                  const struct pam_message **_msg,
                  struct pam_response      **_res,
                  void                      *_udata)
{    
    int                       retval = PAM_CONV_ERR;
    struct pam_response      *resa   = NULL;
    const struct pam_message *m      = NULL;
    struct pam_response      *r      = NULL;
    pam_auto                 *t      = _udata;
    
    resa = calloc(_msgsz, sizeof(struct pam_response));
    if (resa == NULL/*err*/) goto cleanup_buf_err;
    for (int j=0; j<_msgsz; j++) {
        m = _msg[j];
        r = resa+j;
        switch (m->msg_style) {
        case PAM_PROMPT_ECHO_ON:
            r->resp = strdup(t->username);
            if (!r->resp/*err*/) goto cleanup_buf_err;
            break;
        case PAM_PROMPT_ECHO_OFF:
            r->resp = strdup(t->password);
            if (!r->resp/*err*/) goto cleanup_buf_err;
            break;
        case PAM_ERROR_MSG:
            syslog(LOG_ERR, "%s", m->msg);
            if (t->fp) {
                fprintf(t->fp, "%s\n", mtext_get(m->msg));
            }
            break;
        case PAM_TEXT_INFO:
            syslog(LOG_INFO, "%s", m->msg);
            if (t->fp) {
                fprintf(t->fp, "%s\n", mtext_get(m->msg));
            }
            break;
        default:
            goto cleanup_no_style;
        }
    }
    *_res = resa;
    retval = PAM_SUCCESS;
    return retval;
 cleanup_buf_err:
    retval = PAM_BUF_ERR;
    goto cleanup;
 cleanup_no_style:
    retval = PAM_CONV_ERR;
    goto cleanup;
 cleanup:
    for (int i=0; resa && i<_msgsz; i++) {
        free(resa[i].resp);
    }
    return retval;
}

static inline
int pam_start_auto(const char *service, pam_auto *_auto, pam_handle_t **_pamh) {
    struct pam_conv conv = { pam_weblogin_conv, _auto };
    return pam_start(service, _auto->username, &conv, _pamh);
}

#endif
