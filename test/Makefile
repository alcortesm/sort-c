BIN=testall
SRCS=test.c
LIBDIR=../lib/
LIB=sort
INCDIR=../include

OBJS=$(SRCS:.c=.o)
LIBPATH=$(LIBDIR)lib$(LIB).a

ifdef CXX
	CC=$(CXX)
else
	CC=gcc
endif
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99
IFLAGS=-I ../include/
LFLAGS=-L $(LIBDIR) -l $(LIB)
DEBUG=-g

.PHONY: clean test $(LIBPATH)

test: $(BIN) $(LIBPATH)
	valgrind -q ./$(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $(FLAGS) $^ $(IFLAGS) $(LFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(DEBUG) $(IFLAGS) $(LFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJS)
	rm -rf $(BIN)
