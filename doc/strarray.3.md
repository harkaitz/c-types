# NAME

streq2map(), strmap_get()

# SYNOPSIS

    #include <str/strarray.h>
    
    typedef int (*strcmp_f) (const char *s1, const char *s2);
    
    void  streq2map (char *_i[], int _o_sz, char *_o[_o_sz]);
    
    char *strmap_get(char *_a[], const char _key[], strcmp_f _cmp);

# DESCRIPTION

This are functions to handle *map string arrays* and *equal string arrays*.

    char *map[] = {"var1", "val1", "var2", "val2", NULL};
    char *eq[]  = {"var1=val1", "var2=val2", NULL};

The *map string arrays* are easier to forge programmaticaly whilst *equal
string arrays* are better for command line arguments. Use the first to
configure your libraries.

# RETURN VALUE

NULL when not found.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**STRCMP(3)**, **STRCASECMP(3)**
