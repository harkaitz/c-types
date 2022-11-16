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
	@echo "B $@ $<"
	@$(CC) -o $@ $< $(CFLAGS_ALL) $(LIBS)
install: $(PROGRAMS) $(HEADERS)
	@echo "I bin/ $(PROGRAMS)"
	@install -d                $(DESTDIR)$(PREFIX)/bin
	@install -m755 $(PROGRAMS) $(DESTDIR)$(PREFIX)/bin
	@echo "I include/types/ $(HEADERS1)"
	@install -d                $(DESTDIR)$(PREFIX)/include/types/spain
	@install -m644 $(HEADERS1) $(DESTDIR)$(PREFIX)/include/types
	@echo "I include/types/spain/ $(HEADERS2)"
	@install -m644 $(HEADERS2) $(DESTDIR)$(PREFIX)/include/types/spain
clean:
	@echo "D $(PROGRAMS)"
	@rm -f $(PROGRAMS)
## -- gettext --
update: u-locales
u-locales:
	@auto-gettext update
DISABLE_GETTEXT=$(shell which msgfmt >/dev/null 2>&1 || echo y)
ifeq ($(DISABLE_GETTEXT),)
install: install-po
install-po:
	@echo 'MO share/locale/es/LC_MESSAGES/c-types.mo'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/locale/es/LC_MESSAGES
	@rm -f $(DESTDIR)$(PREFIX)/share/locale/es/LC_MESSAGES/c-types.mo
	@msgfmt --output-file=$(DESTDIR)$(PREFIX)/share/locale/es/LC_MESSAGES/c-types.mo ./locales/es/c-types.po
	@echo 'MO share/locale/eu/LC_MESSAGES/c-types.mo'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/locale/eu/LC_MESSAGES
	@rm -f $(DESTDIR)$(PREFIX)/share/locale/eu/LC_MESSAGES/c-types.mo
	@msgfmt --output-file=$(DESTDIR)$(PREFIX)/share/locale/eu/LC_MESSAGES/c-types.mo ./locales/eu/c-types.po
	@echo 'MO share/locale/ca/LC_MESSAGES/c-types.mo'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/locale/ca/LC_MESSAGES
	@rm -f $(DESTDIR)$(PREFIX)/share/locale/ca/LC_MESSAGES/c-types.mo
	@msgfmt --output-file=$(DESTDIR)$(PREFIX)/share/locale/ca/LC_MESSAGES/c-types.mo ./locales/ca/c-types.po
	@echo 'MO share/locale/gl/LC_MESSAGES/c-types.mo'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/locale/gl/LC_MESSAGES
	@rm -f $(DESTDIR)$(PREFIX)/share/locale/gl/LC_MESSAGES/c-types.mo
	@msgfmt --output-file=$(DESTDIR)$(PREFIX)/share/locale/gl/LC_MESSAGES/c-types.mo ./locales/gl/c-types.po
endif
## -- gettext --
## -- manpages --
install: install-man3
install-man3:
	@echo 'I share/man/man3/'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/bool_ss.3'
	@cp ./doc/bool_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/time_ss.3'
	@cp ./doc/time_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/uuid_ss.3'
	@cp ./doc/uuid_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/long_ss.3'
	@cp ./doc/long_ss.3 $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/email.3'
	@cp ./doc/email.3 $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/password.3'
	@cp ./doc/password.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- manpages --
## -- license --
install: install-license
install-license: LICENSE
	@echo 'I share/doc/c-types/LICENSE'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-types
	@cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-types
## -- license --
