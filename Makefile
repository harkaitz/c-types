## Configuration
DESTDIR     =
PREFIX      =/usr/local
AR          =ar
CC          =gcc
CFLAGS      =-Wall -g
CFLAGS_ALL  =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
PROGRAMS    =                  \
    tools/sdate$(EXE)          \
    tools/valid-email$(EXE)    \
    tools/valid-password$(EXE)
HEADERS     =        \
    types/bool_ss.h  \
    types/long_ss.h  \
    types/time_ss.h  \
    types/uuid_ss.h  \
    types/email.h    \
    types/password.h \
    types/username.h \
    types/lstack.h
all: $(PROGRAMS)
tools/%: tools/%.c $(HEADERS)
	$(CC) -o $@ $< $(CFLAGS_ALL) $(LIBS)
install: $(PROGRAMS) $(HEADERS)
	install -d                $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS) $(DESTDIR)$(PREFIX)/bin
	install -d                $(DESTDIR)$(PREFIX)/include/types
	install -m644 $(HEADERS)  $(DESTDIR)$(PREFIX)/include/types
clean:
	rm -f $(PROGRAMS)
## -- manpages --
ifneq ($(PREFIX),)
MAN_3=./doc/email.3 ./doc/password.3 ./doc/uuid_ss.3 ./doc/bool_ss.3 ./doc/long_ss.3 ./doc/time_ss.3 
install: install-man3
install-man3: $(MAN_3)
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp $(MAN_3) $(DESTDIR)$(PREFIX)/share/man/man3
endif
## -- manpages --
## -- license --
ifneq ($(PREFIX),)
install: install-license
install-license: LICENSE
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-types
	cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-types
endif
## -- license --
## -- gettext --
ifneq ($(PREFIX),)
install: install-po
install-po:
	mkdir -p $(DESTDIR)$(PREFIX)/share/locale/es/LC_MESSAGES
	cp locales/es/LC_MESSAGES/c-types.mo $(DESTDIR)$(PREFIX)/share/locale/es/LC_MESSAGES
	mkdir -p $(DESTDIR)$(PREFIX)/share/locale/eu/LC_MESSAGES
	cp locales/eu/LC_MESSAGES/c-types.mo $(DESTDIR)$(PREFIX)/share/locale/eu/LC_MESSAGES
endif
## -- gettext --
