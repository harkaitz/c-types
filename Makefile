## Configuration
DESTDIR     =
PREFIX      =/usr/local
AR          =ar
CC          =gcc
CFLAGS      =-Wall -g
CPPFLAGS    =
LIBS        =
HEADERS_STR =$(shell find include/str   -iregex '.*\.h')
HEADERS_TYP =$(shell find include/types -iregex '.*\.h')
HEADERS_IO  =$(shell find include/io    -iregex '.*\.h')
HEADERS_SYS =$(shell find include/sys   -iregex '.*\.h')
HEADERS_CURL=$(shell find include/curl  -iregex '.*\.h')
MARKDOWNS   =$(shell find doc           -iregex '.*\.md')
MANPAGES_3  =$(shell find doc           -iregex '.*\.3')
PROGRAMS_S  =$(shell find tools         -iregex '.*\.c')
HEADERS     =$(HEADERS_STR) $(HEADERS_TYP) $(HEADERS_IO) $(HEADERS_SYS)
PROGRAMS    =$(patsubst %.c,%,$(PROGRAMS_S))
CFLAGS_ALL  =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
## Help string.
all:
help:
	@echo "all         : Build everything."
	@echo "clean       : Clean files."
	@echo "install     : Install all produced files."
	@echo "ssnip       : Execute 'ssnip' on all files."

## Programs.
all: $(PROGRAMS)
tools/%: tools/%.c $(HEADERS)
	$(CC) -o $@ $<$(CFLAGS_ALL) $(LIBS)

## install and clean.
install:
	install -d                    $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS)     $(DESTDIR)$(PREFIX)/bin
	install -d                    $(DESTDIR)$(PREFIX)/share/man/man3
	install -m644 $(MANPAGES_3)   $(DESTDIR)$(PREFIX)/share/man/man3
	install -d                    $(DESTDIR)$(PREFIX)/include/str
	install -m644 $(HEADERS_STR)  $(DESTDIR)$(PREFIX)/include/str
	install -d                    $(DESTDIR)$(PREFIX)/include/types
	install -m644 $(HEADERS_TYP)  $(DESTDIR)$(PREFIX)/include/types
	install -d                    $(DESTDIR)$(PREFIX)/include/io
	install -m644 $(HEADERS_IO)   $(DESTDIR)$(PREFIX)/include/io
	install -d                    $(DESTDIR)$(PREFIX)/include/sys
	install -m644 $(HEADERS_SYS)  $(DESTDIR)$(PREFIX)/include/sys
	install -d                    $(DESTDIR)$(PREFIX)/include/curl
	install -m644 $(HEADERS_CURL) $(DESTDIR)$(PREFIX)/include/curl

clean:
	rm -f $(PROGRAMS)
ssnip:
	ssnip LICENSE $(HEADERS) $(MARKDOWNS) $(PROGRAMS_S) $(MANPAGES_3) README.md
