# C-TYPES

Collection of types for C.

## String operations.

+ *str/trim.h*        : The very basic trim function for C.    [man](doc/trim.3.md).
+ *str/asprintfa.h*   : Like asprintfa but with alloca().      [man](doc/asprintfa.3.md)
+ *str/str2num.h*     : Make switch() statements with strings. [man](doc/str2num.3.md)
+ *str/random_fill.h* : Create a random string.                [man](doc/random_fill.3.md)
+ *str/memsearch.h*   : Search a string in a memory block.     [man](doc/memsearch.3.md)
+ *str/str2ptr.h*     : Select pointer by string.
+ *str/strarray.h*    : "String equal arrays" and "string maps". [man](doc/strarray.3.md)
+ *str/strdupa.h*     : Concatenate string to stack.
+ *str/mtext.h*       : Internationalization library.
+ *str/phash.h*       : Calculate the MurmurHash64 hash. [man](doc/phash.3.md)

## Header files (You can copy these to your project)

+ *types/email.h*    : Email datatype.         [man](doc/email.3.md)
+ *types/password.h* : Password datatype.      [man](doc/password.3.md)
+ *types/bool_ss.h*  : Boolean string mapping. [man](doc/bool_ss.3.md)
+ *types/coin.h*     : Monetary datatype.      [man](doc/coin.3.md)
+ *types/long_ss.h*  : Secure number parsing.  [man](doc/long_ss.3.md)
+ *types/time_ss.h*  : Calendar day parser.    [man](doc/time_ss.3.md)
+ *types/uuid_ss.h*  : Secure UUID parser.     [man](doc/uuid_ss.3.md)
+ *types/str.h*      : Normalized string sizes.
+ *types/username.h* : Username datatype.

## POSIX C utility headers.

+ *io/fgetpw.h*   : Like *fgets()* but with echoing.                  [man](doc/fgetpw.h)
+ *io/fcopy.h*    : Read from one file pointer and write to another.  [man](doc/fcopy.3.md)
+ *io/prompt.h*   : Read by printing a prompt (only on a tty).        [man](doc/prompt.3.md)
+ *io/findent.h*  : Pretty indented output.        (deprecated)       [man](doc/findent.3.md)
+ *io/stdmsg.h*   : Get logging info for the user. (deprecated)       [man](doc/stdmsg.3.md)

+ *sys/pathsearc.h* : Search files in a path.           [man](doc/pathsearch.3.md)
+ *sys/forkexec.h*  : Wrapper around *fork()* *exec()*.

## ANSI C utility headers.

+ *io/mconfig.h*  : Configuration file reader.                        [man](doc/mconfig.3.md)
+ *io/freplace.h* : Read from a file pointer, replace strings, write. [man](doc/freplace.3.md)

## Security utilities.

+ *sys/authorization.h* : Assign authorizations to threads. [man](doc/sys_authorization.3.md)
+ *pam/pam_auto.h*      : Non interactive pam logins.

## Collaborating

For making bug reports, feature requests and donations visit
one of the following links:

1. [gemini://harkadev.com/oss/](gemini://harkadev.com/oss/)
2. [https://harkadev.com/oss/](https://harkadev.com/oss/)

## TODO

A lot, I only implemented functionality as I needed. If you have something
to add feel free to do so.
