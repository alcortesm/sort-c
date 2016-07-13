LIBNAME=sort
SRCFILES=util.c
SRCDIR=src/
INCDIR=include/
TESTDIR=test/
DEBUGDIR=debug/

OBJDIR=obj/
DEBUGOBJDIR=$(DEBUGDIR)obj/
LIBDIR=lib/
DEBUGLIBDIR=$(DEBUGDIR)lib/

LIB=$(LIBDIR)lib$(LIBNAME).a
DEBUGLIB=$(DEBUGLIBDIR)lib$(LIBNAME).a

SRCS=$(addprefix $(SRCDIR), $(SRCFILES))
OBJS=$(addprefix $(OBJDIR), $(SRCFILES:.c=.o))
DEBUGOBJS=$(addprefix $(DEBUGOBJDIR), $(SRCFILES:.c=.o))

CC?=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99 -O3
DEBUGCFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99 -Og -g --coverage
INCLUDE=-iquote $(INCDIR)

AR?=ar
AFLAGS=-cvr

.PHONY: clean nuke test

$(LIB): $(OBJS) | $(LIBDIR)
	$(AR) $(AFLAGS) $@ $^

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $<

$(LIBDIR):
	mkdir $(LIBDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

$(DEBUGLIB): $(DEBUGOBJS) | $(DEBUGLIBDIR)
	$(AR) $(AFLAGS) $@ $^

$(DEBUGOBJDIR)%.o: $(SRCDIR)%.c | $(DEBUGOBJDIR)
	$(CC) -c $(DEBUGCFLAGS) $(INCLUDE) -o $@ $<

$(DEBUGLIBDIR):
	mkdir -p $(DEBUGLIBDIR)

$(DEBUGOBJDIR):
	mkdir -p $(DEBUGOBJDIR)

test: $(DEBUGLIB)
	cd $(TESTDIR) ; make test

clean:
	rm -rf $(OBJDIR)
	rm -rf $(DEBUGOBJDIR)
	rm -rf $(DEBUGLIBDIR)
	rm -f *.gcov
	cd $(TESTDIR) ; make clean

nuke: clean
	rm -rf $(LIBDIR)
