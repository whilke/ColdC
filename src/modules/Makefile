# Cold driver

CFLAGS=-g -O2 -I../include
LDFLAGS=
LIBS=-lc -lm 
CC=gcc

SYS=linux-gnu
CPU=powerpc
VENDOR=unknown

prefix=..
BINDIR=$(prefix)/bin
SRCDIR=$(prefix)/src
MODULES=$(SRCDIR)/modules

VERSION=1.1.13.1

## we don't need any rules as 'make xxxx.o' will still function correctly,
## and the builds are usually called from ../Makefile anyway.

## Just add the standard rules.

all:

clean:
	rm -f *~ *.BAK *.bak

scrub:
	rm -f *.o *~ *.BAK *.bak

makefile:
	@cd $(prefix); configure -q

install: all

depend:
#	@makedepend -- $(CFLAGS) -- $(SRCS) > /dev/null 2>&1
#	@rm Makefile.bak

lint:
	$(LINT) -u $(SRCS)

patchable: scrub
	@chmod -f u+w Makefile
	@echo "all:" > Makefile
	@echo " @echo \"** Invalid Makefile! **\"" >> Makefile
	@echo " @echo \"** running the configure script ... **\"" >> Makefile
	@echo " @cd ../..; configure" >> Makefile

reconfig:
	cd ..; make reconfig
