BIN=testall
SRCS=test.c
LIBDIR=../lib/
LIB=sort
INCDIR=../include

OBJS=$(SRCS:.c=.o)
LIBPATH=$(LIBDIR)lib$(LIB).a

CC=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99
INCLUDE=-I ../include/
LFLAGS=-L $(LIBDIR) -l $(LIB) -I $(INCDIR)
DEBUG=-g

.PHONY: clean test $(LIBPATH)

test: $(BIN) $(LIBPATH)
	valgrind -q ./$(BIN)

$(BIN): $(OBJS)
	$(CC) -o $@ $(FLAGS) $^

.c.o:
	$(CC) $(CFLAGS) $(LFLAGS) $(DEBUG) -c -o $@ $<

clean:
	rm -rf $(OBJS)
	rm -rf $(BIN)
