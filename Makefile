SRCDIR=src/
INCDIR=include/
LIBDIR=lib/
TESTDIR=test/

LIB=$(LIBDIR)libsort.a
SRCS=$(addprefix $(SRCDIR), util.c)
OBJS=$(SRCS:.c=.o)

ifdef CXX
	CC=$(CXX)
else
	CC=gcc
endif
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99
INCLUDE=-iquote include/

AR=ar
AFLAGS=-cvr

.PHONY: clean test nuke

$(LIB): $(OBJS) | $(LIBDIR)
	$(AR) $(AFLAGS) $@ $<

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c -o $@ $<

$(LIBDIR):
	mkdir $(LIBDIR)

test: $(LIB)
	cd $(TESTDIR) ; make test

clean:
	rm -rf $(OBJS)
	cd $(TESTDIR) ; make clean

nuke: clean
	rm -rf $(LIBDIR)

