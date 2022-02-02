#ifndef SYS_PATHSEARCH_H
#define SYS_PATHSEARCH_H

#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>

static __attribute__((unused))
bool pathsearch (const char _path[], char _sep, const char _name[], char **_o) {
    size_t      l_fil  = strlen(_name);
    const char *s1     = _path;
    const char *s2     = strchr(s1, _sep);
    char       *found  = NULL;
    bool        retval = false;
    while(s1 && s2) {
        size_t l_dir = (s2-s1);
        size_t l_buf = l_dir+1+l_fil+1;
        char b[l_buf];
        memcpy(b, s1, l_dir);
        b[l_dir] = '/';
        memcpy(b+l_dir+1, _name, l_fil+1);
        struct stat sb;
        if (stat(b, &sb) == 0 && sb.st_mode & S_IXUSR) {
            found = malloc(l_buf);
            if (!found/*err*/) goto cleanup_errno;
            memcpy(found, b, l_buf);
            break;
        }
        s1 = s2+1;
        s2 = strchr(s1, _sep);
    }
    if (!found/*err*/) goto cleanup_not_found;
    if (_o) {
        *_o = found;
        found = NULL;
    }
    retval = true;
    goto cleanup;
 cleanup_errno:
    syslog(LOG_ERR, "%s: %s", _name, strerror(errno));
    goto cleanup;
 cleanup_not_found:
    syslog(LOG_ERR, "%s: Not found.", _name);
    goto cleanup;
 cleanup:
    free(found);
    return retval;
}

#endif
