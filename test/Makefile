BIN=testall
SRCS=test.c test_util.c
LIBDIR=../debug/lib/
LIB=sort
INCDIR=../include

OBJS=$(SRCS:.c=.o)
LIBPATH=$(LIBDIR)lib$(LIB).a

CC?=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99
IFLAGS=-I ../include/
LFLAGS=-L $(LIBDIR) -l $(LIB) --coverage
DEBUG=-g

.PHONY: clean test valgrind $(LIBPATH)

test: $(BIN) $(LIBPATH)
	./$(BIN)

valgrind: $(BIN) $(LIBPATH)
	valgrind -q ./$(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(DEBUG) $(IFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	rm -f $(BIN)
