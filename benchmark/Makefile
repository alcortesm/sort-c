BIN=benchmarkall
SRCS=benchmark.c
LIBDIR=../lib/
LIB=sort
INCDIR=../include

OBJS=$(SRCS:.c=.o)
LIBPATH=$(LIBDIR)lib$(LIB).a

CC?=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99 -O3
IFLAGS=-I ../include/
LFLAGS=-L $(LIBDIR) -l $(LIB)

.PHONY: clean benchmark

benchmark: $(BIN)
	./$(BIN)

$(BIN): $(OBJS) $(LIBPATH)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(DEBUG) $(IFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
	rm -f $(BIN)
