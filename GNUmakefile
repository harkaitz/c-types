PROJECT=c-types
VERSION=1.0.0
all:
install:
clean:
## Configuration
DESTDIR     =
PREFIX      =/usr/local
AR          =ar
CC          =cc
CFLAGS      =-Wall -g
CFLAGS_ALL  =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
PROGRAMS    =                  \
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

HEADERS=$(HEADERS1) $(HEADERS2)
all: $(PROGRAMS)
tools/%: tools/%.c $(HEADERS)
	$(CC) -o $@ $< $(CFLAGS_ALL) $(LIBS)
install: $(PROGRAMS) $(HEADERS)
	install -d                $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS) $(DESTDIR)$(PREFIX)/bin
	install -d                $(DESTDIR)$(PREFIX)/include/types/spain
	install -m644 $(HEADERS1) $(DESTDIR)$(PREFIX)/include/types
	install -m644 $(HEADERS2) $(DESTDIR)$(PREFIX)/include/types/spain
clean:
	rm -f $(PROGRAMS)
## -- BLOCK:license --
install: install-license
install-license: 
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
	cp LICENSE README.md $(DESTDIR)$(PREFIX)/share/doc/$(PROJECT)
update: update-license
update-license:
	ssnip README.md
## -- BLOCK:license --
## -- BLOCK:man --
update: update-man
update-man:
	make-h-man update
install: install-man
install-man:
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/uuid_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/long_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/email.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/bool_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/time_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	cp ./doc/password.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- BLOCK:man --
