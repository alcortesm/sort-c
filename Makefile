LIB_NAME=sort
SRC_FILES=util.c array.c bubble.c merge_nspace.c quick.c heap.c
SRC_DIR=src/
INC_DIR=include/
TEST_DIR=test/
BENCHMARK_DIR=benchmark/
DEBUG_DIR=debug/

OBJ_DIR=obj/
DEBUG_OBJ_DIR=$(DEBUG_DIR)obj/
LIB_DIR=lib/
DEBUG_LIB_DIR=$(DEBUG_DIR)lib/

DEBUG_COV_DIR=$(DEBUG_DIR)cov/

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

.PHONY: clean nuke test benchmark valgrind

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

$(DEBUG_COV_DIR):
	mkdir -p $(DEBUG_COV_DIR)

test: $(DEBUG_LIB)
	cd $(TEST_DIR) ; make test

benchmark: $(LIB)
	cd $(BENCHMARK_DIR) ; make benchmark

valgrind: $(DEBUG_LIB)
	cd $(TEST_DIR) ; make valgrind

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(DEBUG_DIR)
	rm -f *.gcov
	cd $(TEST_DIR) ; make clean
	cd $(BENCHMARK_DIR) ; make clean

nuke: clean
	rm -rf $(LIB_DIR)

coverage: test | $(DEBUG_COV_DIR)
	lcov --directory $(DEBUG_OBJ_DIR) --rc lcov_branch_coverage=1 --capture --output-file $(DEBUG_COV_DIR)cov.info
	genhtml -o $(DEBUG_COV_DIR) --rc lcov_branch_coverage=1 $(DEBUG_COV_DIR)cov.info
	@echo "See HTML coverage report at $(PWD)/$(DEBUG_COV_DIR)index.html"
