# NAME

prompt_fgets(), prompt_fgetpw()

# SYNOPSIS

    #include <io/prompt.h>
    char *prompt_fgets  (const char _prompt[], char _b[], size_t _blen);
    char *prompt_fgetpw (const char _prompt[], char _b[], size_t _blen);

# DESCRIPTION

Prompt a message (if prompt not null and stdin is a tty) and read a line. The trailing
newline is removed. Requires all the precautions as *fgets(3)*.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

# SEE ALSO

**FGETS(3)**, **PROMPT(3)**
