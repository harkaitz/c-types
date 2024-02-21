PROJECT=c-types
VERSION=1.0.0
DESTDIR=
PREFIX =/usr/local
CC     =gcc -pedantic-errors -std=c99 -Wall
PROGRAMS=                      \
    tools/sdate$(EXE)          \
    tools/valid-email$(EXE)    \
    tools/valid-password$(EXE) \
    tools/valid-dni$(EXE)      \
    tools/random-dni$(EXE)
HEADERS1=            \
    types/bool_ss.h  \
    types/long_ss.h  \
    types/time_ss.h  \
    types/uuid_ss.h  \
    types/email.h    \
    types/password.h \
    types/username.h \
    types/lstack.h
HEADERS2=            \
    types/spain/dni.h
all:
install:
clean:
##
CFLAGS_ALL =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
HEADERS    =$(HEADERS1) $(HEADERS2)
all: $(PROGRAMS)
tools/%: tools/%.c $(HEADERS)
	$(CC) -o $@ $< $(CFLAGS_ALL) $(LIBS)
install: $(PROGRAMS) $(HEADERS)
	@install -d                $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS) $(DESTDIR)$(PREFIX)/bin
	@install -d                $(DESTDIR)$(PREFIX)/include/types/spain
	install -m644 $(HEADERS1) $(DESTDIR)$(PREFIX)/include/types
	install -m644 $(HEADERS2) $(DESTDIR)$(PREFIX)/include/types/spain
clean:
	rm -f $(PROGRAMS)
## -- BLOCK:license --
install: install-license
install-license: 
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	cp LICENSE  $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
## -- BLOCK:license --
## -- BLOCK:man --
install: install-man
install-man:
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/uuid_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/long_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/email.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/bool_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/time_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/password.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- BLOCK:man --
