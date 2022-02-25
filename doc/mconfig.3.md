# NAME

MCONFIG_INITIALIZER(),mconfig_cleanup(),mconfig_load(),mconfig_get(),
mconfig_set(),mconfig_printf(),mconfig_require()

# SYNOPSIS

    #include <io/mconfig.h>
    
    mconfig_t MCONFIG_INITIALIZER(void);
    
    void mconfig_cleanup (mconfig_t *_m);
    bool mconfig_add     (mconfig_t *_m, ...);
    bool mconfig_load    (mconfig_t *_m, const char _filename[], bool _success_if_not_found);
    cstr mconfig_get     (mconfig_t *_m, const char _var[], const char _def[]);
    int  mconfig_printf  (mconfig_t *_m, FILE *_f, const char _cfg[], ...);

# DESCRIPTION

This functions help reading a configuration file with lines formated the
following way.

    VARIABLE_NAME     VALUE
    # COMMENT

You can initialize the mconfig_t structure by zeroing it. After the program
finishes you can call *mconfig_cleanup()*.

Load a file with *mconfig_load()*. If a configuration was set previously then
*mconfig_load()* will ignore it. This means you should call it the following
order.

    mconfig_load(&m, "/etc/my-program.cfg", true);

You can get a configuration variable with *mconfig_get()* and change/set one
with *mconfig_set()*. When changing the old value will be kept, so do not
set ovewrite values many times, that would be a leak.

You can write a configuration file with *mconfig_printf()*.

# RETURN VALUE

True on success, false on error.

# COLLABORATING

For making bug reports, feature requests and donations visit one of the
following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

