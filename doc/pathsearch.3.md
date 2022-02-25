# NAME

pathsearch()

# SYNOPSIS

    #include <sys/pathsearch.h>
    
    #define PATH_SEP ':'(unix)';'(windows)
    
    bool pathsearch(const char _path[],
                    char       _sep,
                    const char _name[],
                    char     **_o);

# DESCRIPTION

Search executable named *_name* in a directory list in *_path* separated by *_sep*. The
result is stored in *_o* and must be freed with *free()*. It returns *true* on
success and *false* in case of error.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

