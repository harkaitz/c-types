#ifndef SYS_PATHSEARCH_H
#define SYS_PATHSEARCH_H

#include <sys/stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <errno.h>
#include <stdio.h>


static __attribute__((unused))
bool pathsearch (const char _path[], char _sep, const char _name[], char **_o) {
    char       *found  = NULL;
    bool        retval = false;
    char        path[strlen(_path)+1];
    char        seps[] = {_sep, '\0'};
    char       *s2,*s1;
    strcpy(path, _path);

    
    for(s1 = strtok_r(path, seps, &s2); s1; s1 = strtok_r(NULL, seps, &s2)) {
        char b[strlen(s1)+1+strlen(_name)+1];
        sprintf(b, "%s/%s", s1, _name);
        struct stat sb = {0};
        if ((stat(b, &sb) == 0) && (sb.st_mode & S_IXUSR)) {
            found = strdup(b);
            if (!found/*err*/) goto cleanup_errno;
            break;
        }
    }
    if (!found/*err*/) goto cleanup_not_found;
    if (_o) {
        *_o = found;
        found = NULL;
    }
    retval = true;
 cleanup:
    free(found);
    return retval;
 cleanup_errno:
    syslog(LOG_ERR, "%s: %s", _name, strerror(errno));
    goto cleanup;
 cleanup_not_found:
    syslog(LOG_ERR, "%s: Not found.", _name);
    goto cleanup;
 
}

#ifndef PATH_SEP
#  ifdef _WIN32
#    define PATH_SEP ';'
#  else
#    define PATH_SEP ':'
#  endif
#endif

#endif
