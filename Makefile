LIBNAME=sort
SRCFILES=util.c
SRCDIR=src/
INCDIR=include/
TESTDIR=test/

OBJDIR=obj/
LIBDIR=lib/

LIB=$(LIBDIR)lib$(LIBNAME).a
SRCS=$(addprefix $(SRCDIR), $(SRCFILES))
OBJS=$(addprefix $(OBJDIR), $(SRCFILES:.c=.o))

CC?=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99 --coverage
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

test: $(LIB)
	cd $(TESTDIR) ; make test

clean:
	rm -rf $(OBJDIR)
	rm -f $(SRCDIR)*.gcda
	rm -f $(SRCDIR)*.gcno
	rm -f *.gcov
	cd $(TESTDIR) ; make clean

nuke: clean
	rm -rf $(LIBDIR)
