SRCDIR=src/
INCDIR=include/
LIBDIR=lib/
TESTDIR=test/

LIB=$(LIBDIR)libsort.a
SRCS=$(addprefix $(SRCDIR), util.c)
OBJS=$(SRCS:.c=.o)

CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99
INCLUDE=-iquote include/

AR=ar
AFLAGS=-cvr

.PHONY: clean test nuke

test: $(LIB)
	cd $(TESTDIR) ; make test

$(LIB): $(OBJS) | $(LIBDIR)
	$(AR) $(AFLAGS) $@ $<

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c -o $@ $<

$(LIBDIR):
	mkdir $(LIBDIR)

clean:
	rm -rf $(OBJS)
	cd $(TESTDIR) ; make clean

nuke: clean
	rm -rf $(LIBDIR)

