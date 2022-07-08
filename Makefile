## Configuration
DESTDIR     =
PREFIX      =/usr/local
AR          =ar
CC          =gcc
CFLAGS      =-Wall -g -rdynamic
CPPFLAGS    =-DRELEASE
LIBS        =
HEADERS_STR   =$(shell find include/str      -iregex '.*\.h')
HEADERS_TYPES =$(shell find include/types    -iregex '.*\.h')
HEADERS_IO    =$(shell find include/io       -iregex '.*\.h')
HEADERS_SYS   =$(shell find include/sys      -iregex '.*\.h')
MARKDOWNS     =$(shell find doc              -iregex '.*\.md')
MANPAGES_1    =$(shell find doc              -iregex '.*\.1')
MANPAGES_3    =$(shell find doc              -iregex '.*\.3')
PROGRAMS_S    =$(shell find tools            -iregex '.*\.c')
HEADERS     =                                             \
    $(HEADERS_STR)      $(HEADERS_TYPES)  $(HEADERS_IO)   \
    $(HEADERS_SYS)
PROGRAMS    =$(patsubst %.c,%,$(PROGRAMS_S))
CFLAGS_ALL  =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
## Help string.
all:
help:
	@echo "all         : Build everything."
	@echo "clean       : Clean files."
	@echo "install     : Install all produced files."

## Programs.
all: $(PROGRAMS)
tools/%: tools/%.c $(HEADERS)
	$(CC) -o $@ $< $(CFLAGS_ALL) $(LIBS)

## install and clean.
install:
	install -d                     $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS)      $(DESTDIR)$(PREFIX)/bin
	install -d                     $(DESTDIR)$(PREFIX)/share/man/man3
	install -m644 $(MANPAGES_3)    $(DESTDIR)$(PREFIX)/share/man/man3
	install -d                     $(DESTDIR)$(PREFIX)/share/man/man1
	install -m644 $(MANPAGES_1)    $(DESTDIR)$(PREFIX)/share/man/man1
	install -d                     $(DESTDIR)$(PREFIX)/include/str
	install -m644 $(HEADERS_STR)   $(DESTDIR)$(PREFIX)/include/str
	install -d                     $(DESTDIR)$(PREFIX)/include/types
	install -m644 $(HEADERS_TYPES) $(DESTDIR)$(PREFIX)/include/types
	install -d                     $(DESTDIR)$(PREFIX)/include/io
	install -m644 $(HEADERS_IO)    $(DESTDIR)$(PREFIX)/include/io
	install -d                     $(DESTDIR)$(PREFIX)/include/sys
	install -m644 $(HEADERS_SYS)   $(DESTDIR)$(PREFIX)/include/sys
clean:
	rm -f $(PROGRAMS)
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
