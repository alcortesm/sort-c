LIB_NAME=sort
SRC_FILES=util.c
SRC_DIR=src/
INC_DIR=include/
TEST_DIR=test/
DEBUG_DIR=debug/

OBJ_DIR=obj/
DEBUG_OBJ_DIR=$(DEBUG_DIR)obj/
LIB_DIR=lib/
DEBUG_LIB_DIR=$(DEBUG_DIR)lib/

LIB=$(LIB_DIR)lib$(LIB_NAME).a
DEBUG_LIB=$(DEBUG_LIB_DIR)lib$(LIB_NAME).a

SRCS=$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS=$(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))
DEBUG_OBJS=$(addprefix $(DEBUG_OBJ_DIR), $(SRC_FILES:.c=.o))

CC?=gcc
CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99 -O3
DEBUG_CFLAGS=-Wall -Wextra -Wpedantic -Werror -std=c99 -Og -g --coverage
INCLUDE=-iquote $(INC_DIR)

AR?=ar
AFLAGS=-cvr

.PHONY: clean nuke test

$(LIB): $(OBJS) | $(LIB_DIR)
	$(AR) $(AFLAGS) $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDE) -o $@ $<

$(LIB_DIR):
	mkdir $(LIB_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(DEBUG_LIB): $(DEBUG_OBJS) | $(DEBUG_LIB_DIR)
	$(AR) $(AFLAGS) $@ $^

$(DEBUG_OBJ_DIR)%.o: $(SRC_DIR)%.c | $(DEBUG_OBJ_DIR)
	$(CC) -c $(DEBUG_CFLAGS) $(INCLUDE) -o $@ $<

$(DEBUG_LIB_DIR):
	mkdir -p $(DEBUG_LIB_DIR)

$(DEBUG_OBJ_DIR):
	mkdir -p $(DEBUG_OBJ_DIR)

test: $(DEBUG_LIB)
	cd $(TEST_DIR) ; make test

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(DEBUG_OBJ_DIR)
	rm -rf $(DEBUG_LIB_DIR)
	rm -f *.gcov
	cd $(TEST_DIR) ; make clean

nuke: clean
	rm -rf $(LIB_DIR)
