# NAME

str2num()

# SYNOPSIS

    #include <str/str2num.h>
    int str2num(const char *s1, int (*f) (const char *,const char *), ...);

# DESCRIPTION

The C standard doesn't define a mechanism to build switch statements out of
strings. Long if/strcmp structures can be complecated to read. This function
solves this issue.

    #include <str/str2num.h>
    
    switch(str2num(s, strcasecmp, "opt1", 1, "opt2", 2, NULL)) {
    case 1: ... break;
    case 2: ... break;
    default: ... break;
    }

# RETURN VALUE

If not found it returns -1, if *s* is null it returns -2.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**STRCMP(3)**, **STRCASECMP(3)**
