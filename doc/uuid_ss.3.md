# NAME

uuid_str(), uuid_str_2()

# SYNOPSIS

    #include <types/uuid_ss.h>
    
    const char *uuid_str  (const uuid_t _uuid, uuid_ss *_uuid_ss);
    const char *uuid_str_2(const char _prefix[], const uuid_t _uuid, size_t _bsz, char _b[]);

# DESCRIPTION

Use this two functions to unparse UUIDs securely.

# COLLABORATING

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

