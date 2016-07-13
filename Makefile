SRCDIR=src/
INCDIR=include/
LIBDIR=lib/
TESTDIR=test/

LIB=$(LIBDIR)libsort.a
SRCS=$(addprefix $(SRCDIR), util.c)
OBJS=$(SRCS:.c=.o)

CC?=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99 --coverage
INCLUDE=-iquote include/

AR=ar
AFLAGS=-cvr

.PHONY: clean nuke test

$(LIB): $(OBJS) | $(LIBDIR)
	$(AR) $(AFLAGS) $@ $<

.c.o:
	$(CC) $(CFLAGS) $(INCLUDE) $(DEBUG) -c -o $@ $<

$(LIBDIR):
	mkdir $(LIBDIR)

test: $(LIB)
	cd $(TESTDIR) ; make test

clean:
	rm -f $(OBJS)
	rm -f $(SRCDIR)*.gcda
	rm -f $(SRCDIR)*.gcno
	rm -f *.gcov
	cd $(TESTDIR) ; make clean

nuke: clean
	rm -rf $(LIBDIR)
