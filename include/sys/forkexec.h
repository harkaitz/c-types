#ifndef FORKEXEC_H
#define FORKEXEC_H

#include "pathsearch.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/wait.h>

static __attribute__((unused))
bool forkexec_a (pid_t *_pid, int _fd0, int _fd1, int _fd2, char *_cmd[]) {
    int   res;
    pid_t pid  = -1;
    char *prog = NULL;
    res = pathsearch(getenv("PATH"), PATH_SEP, _cmd[0], &prog);
    if (!res/*err*/) return false;
    if ((pid = fork())==0) {
        int fd0 = _fd0, fd1 = _fd1, fd2 = _fd2; 
        if (fd0==-1) {
            fd0 = open("/dev/null", O_RDONLY);
            if (fd0==-1) exit(1);
        }
        if (fd1==-1) {
            fd1 = open("/dev/null", O_WRONLY);
            if (fd1==-1) exit(1);
        }
        if (fd2==-1) {
            fd2 = open("/dev/null", O_WRONLY);
            if (fd2==-1) exit(1);
        }
        if (fd0!=0)           { dup2(fd0, 0); }
        if (fd1!=1)           { dup2(fd1, 1); }
        if (fd2!=2)           { dup2(fd2, 2); }
        if (fd0!=0)           { close(fd0);   }
        if (fd1!=1 && fd1!=2) { close(fd1);   }
        if (fd2!=1 && fd2!=2) { close(fd2);   }
        _cmd[0] = prog;
        execv(prog, _cmd);
        syslog(LOG_ERR, "Can't execute %s: %s", prog, strerror(errno));
        exit(1);
    }
    free(prog);
    if (pid==-1/*err*/) { syslog(LOG_ERR, "%s", strerror(errno)); return false; }
    *_pid = pid;
    return true;
}

static __attribute__((unused))
bool forkexec (pid_t *_pid, int _fd0, int _fd1, int _fd2, char *_prog, ...) {
    va_list va;
    char   *cmd[100] = {_prog, 0};
    int     i = 1;
    va_start(va, _prog);
    while ((cmd[i] = va_arg(va, char *))) { i++; }
    va_end(va);
    return forkexec_a(_pid, _fd0, _fd1, _fd2, cmd);
}

static __attribute__((unused))
bool waitpidret (pid_t _pid, int *_opt_rcode) {
    int res,status;
    res = waitpid(_pid, &status, 0);
    if (res<0/*err*/) { syslog(LOG_ERR, "%s", strerror(errno)); return false; }
    if (!_opt_rcode) {
        
    } else if (!WIFEXITED(status)) {
        *_opt_rcode = 1;
    } else {
        *_opt_rcode = WEXITSTATUS(status);
    }
    return true;
}



#endif
