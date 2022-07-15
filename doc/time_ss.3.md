# NAME

time_day_printf(), time_day_str(), time_day_parse()

# SYNOPSIS

    #include <types/time_ss.h>
    
    typedef struct time_ss {
        char s[32];
    } time_ss;

    typedef enum time_day_err_e {
        TIME_DAY_ERR_NULL_VALUE    = 0,
        TIME_DAY_ERR_MISSING_YEAR  = 1,
        TIME_DAY_ERR_MISSING_MONTH = 2,
        TIME_DAY_ERR_MISSING_DAY   = 3,
        TIME_DAY_ERR_INVALID_YEAR  = 4,
        TIME_DAY_ERR_INVALID_MONTH = 5,
        TIME_DAY_ERR_INVALID_DAY   = 6,
        TIME_DAY_ERR_MAX           = 7
    } time_day_err_e;

    int         time_day_printf (char *b, size_t bsz, time_t _t);
    const char *time_day_str    (time_t  _t, time_ss *_ts);
    bool        time_day_parse  (time_t *_t, const char _s[], time_day_err_e *_opt_reason);

# COLLABORATING

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

