#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sort.h>
#include <util.h>

typedef struct {
    int* a;
    int n;
} array;

array* array_new(int* a, int n);
array* array_clone(array* a);
void   array_free(array* a);

int test_sort_fn(sort_fn fn, const char* prefix);
int is_sorted(int* a, int n);

array tests[] = {
    {NULL, 0},
    {(int[]){0}, 1},
    {(int[]){0, 1}, 2},
    {(int[]){1, 0}, 2},
    {(int[]){0, 1, 2}, 3},
    {(int[]){0, 2, 1}, 3},
    {(int[]){1, 0, 2}, 3},
    {(int[]){1, 2, 0}, 3},
    {(int[]){2, 1, 0}, 3},
    {(int[]){2, 0, 1}, 3},
    {(int[]){0, 1, 2, 3}, 4},
    {(int[]){0, 1, 3, 2}, 4},
    {(int[]){0, 2, 1, 3}, 4},
    {(int[]){0, 2, 3, 1}, 4},
    {(int[]){0, 3, 1, 2}, 4},
    {(int[]){0, 3, 2, 1}, 4},
    {(int[]){1, 0, 3, 2}, 4},
    {(int[]){1, 0, 2, 3}, 4},
    {(int[]){1, 2, 3, 0}, 4},
    {(int[]){1, 2, 0, 3}, 4},
    {(int[]){1, 3, 2, 0}, 4},
    {(int[]){1, 3, 0, 2}, 4},
    {(int[]){2, 0, 1, 3}, 4},
    {(int[]){2, 0, 3, 1}, 4},
    {(int[]){2, 1, 0, 3}, 4},
    {(int[]){2, 1, 3, 0}, 4},
    {(int[]){2, 3, 0, 1}, 4},
    {(int[]){2, 3, 1, 0}, 4},
    {(int[]){3, 0, 2, 1}, 4},
    {(int[]){3, 0, 1, 2}, 4},
    {(int[]){3, 1, 2, 0}, 4},
    {(int[]){3, 1, 0, 2}, 4},
    {(int[]){3, 2, 1, 0}, 4},
    {(int[]){3, 2, 0, 1}, 4},
    {(int[]){0, 1, 2, 3, 4}, 5},
    {(int[]){0, 1, 2, 4, 3}, 5},
    {(int[]){0, 1, 3, 2, 4}, 5},
    {(int[]){0, 1, 3, 4, 2}, 5},
    {(int[]){0, 1, 4, 2, 3}, 5},
    {(int[]){0, 1, 4, 3, 2}, 5},
    {(int[]){0, 2, 1, 3, 4}, 5},
    {(int[]){0, 2, 1, 4, 3}, 5},
    {(int[]){0, 2, 3, 1, 4}, 5},
    {(int[]){0, 2, 3, 4, 1}, 5},
    {(int[]){0, 2, 4, 1, 3}, 5},
    {(int[]){0, 2, 4, 3, 1}, 5},
    {(int[]){0, 3, 1, 2, 4}, 5},
    {(int[]){0, 3, 1, 4, 2}, 5},
    {(int[]){0, 3, 2, 1, 4}, 5},
    {(int[]){0, 3, 2, 4, 1}, 5},
    {(int[]){0, 3, 4, 1, 2}, 5},
    {(int[]){0, 3, 4, 2, 1}, 5},
    {(int[]){0, 4, 1, 2, 3}, 5},
    {(int[]){0, 4, 1, 3, 2}, 5},
    {(int[]){0, 4, 2, 1, 3}, 5},
    {(int[]){0, 4, 2, 3, 1}, 5},
    {(int[]){0, 4, 3, 1, 2}, 5},
    {(int[]){0, 4, 3, 2, 1}, 5},
    {(int[]){1, 0, 2, 3, 4}, 5},
    {(int[]){1, 0, 2, 4, 3}, 5},
    {(int[]){1, 0, 3, 2, 4}, 5},
    {(int[]){1, 0, 3, 4, 2}, 5},
    {(int[]){1, 0, 4, 2, 3}, 5},
    {(int[]){1, 0, 4, 3, 2}, 5},
    {(int[]){1, 2, 0, 3, 4}, 5},
    {(int[]){1, 2, 0, 4, 3}, 5},
    {(int[]){1, 2, 3, 0, 4}, 5},
    {(int[]){1, 2, 3, 4, 0}, 5},
    {(int[]){1, 2, 4, 0, 3}, 5},
    {(int[]){1, 2, 4, 3, 0}, 5},
    {(int[]){1, 3, 0, 2, 4}, 5},
    {(int[]){1, 3, 0, 4, 2}, 5},
    {(int[]){1, 3, 2, 0, 4}, 5},
    {(int[]){1, 3, 2, 4, 0}, 5},
    {(int[]){1, 3, 4, 0, 2}, 5},
    {(int[]){1, 3, 4, 2, 0}, 5},
    {(int[]){1, 4, 0, 2, 3}, 5},
    {(int[]){1, 4, 0, 3, 2}, 5},
    {(int[]){1, 4, 2, 0, 3}, 5},
    {(int[]){1, 4, 2, 3, 0}, 5},
    {(int[]){1, 4, 3, 0, 2}, 5},
    {(int[]){1, 4, 3, 2, 0}, 5},
    {(int[]){2, 0, 1, 3, 4}, 5},
    {(int[]){2, 0, 1, 4, 3}, 5},
    {(int[]){2, 0, 3, 1, 4}, 5},
    {(int[]){2, 0, 3, 4, 1}, 5},
    {(int[]){2, 0, 4, 1, 3}, 5},
    {(int[]){2, 0, 4, 3, 1}, 5},
    {(int[]){2, 1, 0, 3, 4}, 5},
    {(int[]){2, 1, 0, 4, 3}, 5},
    {(int[]){2, 1, 3, 0, 4}, 5},
    {(int[]){2, 1, 3, 4, 0}, 5},
    {(int[]){2, 1, 4, 0, 3}, 5},
    {(int[]){2, 1, 4, 3, 0}, 5},
    {(int[]){2, 3, 0, 1, 4}, 5},
    {(int[]){2, 3, 0, 4, 1}, 5},
    {(int[]){2, 3, 1, 0, 4}, 5},
    {(int[]){2, 3, 1, 4, 0}, 5},
    {(int[]){2, 3, 4, 0, 1}, 5},
    {(int[]){2, 3, 4, 1, 0}, 5},
    {(int[]){2, 4, 0, 1, 3}, 5},
    {(int[]){2, 4, 0, 3, 1}, 5},
    {(int[]){2, 4, 1, 0, 3}, 5},
    {(int[]){2, 4, 1, 3, 0}, 5},
    {(int[]){2, 4, 3, 0, 1}, 5},
    {(int[]){2, 4, 3, 1, 0}, 5},
    {(int[]){3, 0, 1, 2, 4}, 5},
    {(int[]){3, 0, 1, 4, 2}, 5},
    {(int[]){3, 0, 2, 1, 4}, 5},
    {(int[]){3, 0, 2, 4, 1}, 5},
    {(int[]){3, 0, 4, 1, 2}, 5},
    {(int[]){3, 0, 4, 2, 1}, 5},
    {(int[]){3, 1, 0, 2, 4}, 5},
    {(int[]){3, 1, 0, 4, 2}, 5},
    {(int[]){3, 1, 2, 0, 4}, 5},
    {(int[]){3, 1, 2, 4, 0}, 5},
    {(int[]){3, 1, 4, 0, 2}, 5},
    {(int[]){3, 1, 4, 2, 0}, 5},
    {(int[]){3, 2, 0, 1, 4}, 5},
    {(int[]){3, 2, 0, 4, 1}, 5},
    {(int[]){3, 2, 1, 0, 4}, 5},
    {(int[]){3, 2, 1, 4, 0}, 5},
    {(int[]){3, 2, 4, 0, 1}, 5},
    {(int[]){3, 2, 4, 1, 0}, 5},
    {(int[]){3, 4, 0, 1, 2}, 5},
    {(int[]){3, 4, 0, 2, 1}, 5},
    {(int[]){3, 4, 1, 0, 2}, 5},
    {(int[]){3, 4, 1, 2, 0}, 5},
    {(int[]){3, 4, 2, 0, 1}, 5},
    {(int[]){3, 4, 2, 1, 0}, 5},
    {(int[]){4, 0, 1, 2, 3}, 5},
    {(int[]){4, 0, 1, 3, 2}, 5},
    {(int[]){4, 0, 2, 1, 3}, 5},
    {(int[]){4, 0, 2, 3, 1}, 5},
    {(int[]){4, 0, 3, 1, 2}, 5},
    {(int[]){4, 0, 3, 2, 1}, 5},
    {(int[]){4, 1, 0, 2, 3}, 5},
    {(int[]){4, 1, 0, 3, 2}, 5},
    {(int[]){4, 1, 2, 0, 3}, 5},
    {(int[]){4, 1, 2, 3, 0}, 5},
    {(int[]){4, 1, 3, 0, 2}, 5},
    {(int[]){4, 1, 3, 2, 0}, 5},
    {(int[]){4, 2, 0, 1, 3}, 5},
    {(int[]){4, 2, 0, 3, 1}, 5},
    {(int[]){4, 2, 1, 0, 3}, 5},
    {(int[]){4, 2, 1, 3, 0}, 5},
    {(int[]){4, 2, 3, 0, 1}, 5},
    {(int[]){4, 2, 3, 1, 0}, 5},
    {(int[]){4, 3, 0, 1, 2}, 5},
    {(int[]){4, 3, 0, 2, 1}, 5},
    {(int[]){4, 3, 1, 0, 2}, 5},
    {(int[]){4, 3, 1, 2, 0}, 5},
    {(int[]){4, 3, 2, 0, 1}, 5},
    {(int[]){4, 3, 2, 1, 0}, 5},
    {(int[]){0, 1, 2, 3, 4, 5}, 6},
    {(int[]){0, 1, 2, 3, 5, 4}, 6},
    {(int[]){0, 1, 2, 4, 3, 5}, 6},
    {(int[]){0, 1, 2, 4, 5, 3}, 6},
    {(int[]){0, 1, 2, 5, 3, 4}, 6},
    {(int[]){0, 1, 2, 5, 4, 3}, 6},
    {(int[]){0, 1, 3, 2, 4, 5}, 6},
    {(int[]){0, 1, 3, 2, 5, 4}, 6},
    {(int[]){0, 1, 3, 4, 2, 5}, 6},
    {(int[]){0, 1, 3, 4, 5, 2}, 6},
    {(int[]){0, 1, 3, 5, 2, 4}, 6},
    {(int[]){0, 1, 3, 5, 4, 2}, 6},
    {(int[]){0, 1, 4, 2, 3, 5}, 6},
    {(int[]){0, 1, 4, 2, 5, 3}, 6},
    {(int[]){0, 1, 4, 3, 2, 5}, 6},
    {(int[]){0, 1, 4, 3, 5, 2}, 6},
    {(int[]){0, 1, 4, 5, 2, 3}, 6},
    {(int[]){0, 1, 4, 5, 3, 2}, 6},
    {(int[]){0, 1, 5, 2, 3, 4}, 6},
    {(int[]){0, 1, 5, 2, 4, 3}, 6},
    {(int[]){0, 1, 5, 3, 2, 4}, 6},
    {(int[]){0, 1, 5, 3, 4, 2}, 6},
    {(int[]){0, 1, 5, 4, 2, 3}, 6},
    {(int[]){0, 1, 5, 4, 3, 2}, 6},
    {(int[]){0, 2, 1, 3, 4, 5}, 6},
    {(int[]){0, 2, 1, 3, 5, 4}, 6},
    {(int[]){0, 2, 1, 4, 3, 5}, 6},
    {(int[]){0, 2, 1, 4, 5, 3}, 6},
    {(int[]){0, 2, 1, 5, 3, 4}, 6},
    {(int[]){0, 2, 1, 5, 4, 3}, 6},
    {(int[]){0, 2, 3, 1, 4, 5}, 6},
    {(int[]){0, 2, 3, 1, 5, 4}, 6},
    {(int[]){0, 2, 3, 4, 1, 5}, 6},
    {(int[]){0, 2, 3, 4, 5, 1}, 6},
    {(int[]){0, 2, 3, 5, 1, 4}, 6},
    {(int[]){0, 2, 3, 5, 4, 1}, 6},
    {(int[]){0, 2, 4, 1, 3, 5}, 6},
    {(int[]){0, 2, 4, 1, 5, 3}, 6},
    {(int[]){0, 2, 4, 3, 1, 5}, 6},
    {(int[]){0, 2, 4, 3, 5, 1}, 6},
    {(int[]){0, 2, 4, 5, 1, 3}, 6},
    {(int[]){0, 2, 4, 5, 3, 1}, 6},
    {(int[]){0, 2, 5, 1, 3, 4}, 6},
    {(int[]){0, 2, 5, 1, 4, 3}, 6},
    {(int[]){0, 2, 5, 3, 1, 4}, 6},
    {(int[]){0, 2, 5, 3, 4, 1}, 6},
    {(int[]){0, 2, 5, 4, 1, 3}, 6},
    {(int[]){0, 2, 5, 4, 3, 1}, 6},
    {(int[]){0, 3, 1, 2, 4, 5}, 6},
    {(int[]){0, 3, 1, 2, 5, 4}, 6},
    {(int[]){0, 3, 1, 4, 2, 5}, 6},
    {(int[]){0, 3, 1, 4, 5, 2}, 6},
    {(int[]){0, 3, 1, 5, 2, 4}, 6},
    {(int[]){0, 3, 1, 5, 4, 2}, 6},
    {(int[]){0, 3, 2, 1, 4, 5}, 6},
    {(int[]){0, 3, 2, 1, 5, 4}, 6},
    {(int[]){0, 3, 2, 4, 1, 5}, 6},
    {(int[]){0, 3, 2, 4, 5, 1}, 6},
    {(int[]){0, 3, 2, 5, 1, 4}, 6},
    {(int[]){0, 3, 2, 5, 4, 1}, 6},
    {(int[]){0, 3, 4, 1, 2, 5}, 6},
    {(int[]){0, 3, 4, 1, 5, 2}, 6},
    {(int[]){0, 3, 4, 2, 1, 5}, 6},
    {(int[]){0, 3, 4, 2, 5, 1}, 6},
    {(int[]){0, 3, 4, 5, 1, 2}, 6},
    {(int[]){0, 3, 4, 5, 2, 1}, 6},
    {(int[]){0, 3, 5, 1, 2, 4}, 6},
    {(int[]){0, 3, 5, 1, 4, 2}, 6},
    {(int[]){0, 3, 5, 2, 1, 4}, 6},
    {(int[]){0, 3, 5, 2, 4, 1}, 6},
    {(int[]){0, 3, 5, 4, 1, 2}, 6},
    {(int[]){0, 3, 5, 4, 2, 1}, 6},
    {(int[]){0, 4, 1, 2, 3, 5}, 6},
    {(int[]){0, 4, 1, 2, 5, 3}, 6},
    {(int[]){0, 4, 1, 3, 2, 5}, 6},
    {(int[]){0, 4, 1, 3, 5, 2}, 6},
    {(int[]){0, 4, 1, 5, 2, 3}, 6},
    {(int[]){0, 4, 1, 5, 3, 2}, 6},
    {(int[]){0, 4, 2, 1, 3, 5}, 6},
    {(int[]){0, 4, 2, 1, 5, 3}, 6},
    {(int[]){0, 4, 2, 3, 1, 5}, 6},
    {(int[]){0, 4, 2, 3, 5, 1}, 6},
    {(int[]){0, 4, 2, 5, 1, 3}, 6},
    {(int[]){0, 4, 2, 5, 3, 1}, 6},
    {(int[]){0, 4, 3, 1, 2, 5}, 6},
    {(int[]){0, 4, 3, 1, 5, 2}, 6},
    {(int[]){0, 4, 3, 2, 1, 5}, 6},
    {(int[]){0, 4, 3, 2, 5, 1}, 6},
    {(int[]){0, 4, 3, 5, 1, 2}, 6},
    {(int[]){0, 4, 3, 5, 2, 1}, 6},
    {(int[]){0, 4, 5, 1, 2, 3}, 6},
    {(int[]){0, 4, 5, 1, 3, 2}, 6},
    {(int[]){0, 4, 5, 2, 1, 3}, 6},
    {(int[]){0, 4, 5, 2, 3, 1}, 6},
    {(int[]){0, 4, 5, 3, 1, 2}, 6},
    {(int[]){0, 4, 5, 3, 2, 1}, 6},
    {(int[]){0, 5, 1, 2, 3, 4}, 6},
    {(int[]){0, 5, 1, 2, 4, 3}, 6},
    {(int[]){0, 5, 1, 3, 2, 4}, 6},
    {(int[]){0, 5, 1, 3, 4, 2}, 6},
    {(int[]){0, 5, 1, 4, 2, 3}, 6},
    {(int[]){0, 5, 1, 4, 3, 2}, 6},
    {(int[]){0, 5, 2, 1, 3, 4}, 6},
    {(int[]){0, 5, 2, 1, 4, 3}, 6},
    {(int[]){0, 5, 2, 3, 1, 4}, 6},
    {(int[]){0, 5, 2, 3, 4, 1}, 6},
    {(int[]){0, 5, 2, 4, 1, 3}, 6},
    {(int[]){0, 5, 2, 4, 3, 1}, 6},
    {(int[]){0, 5, 3, 1, 2, 4}, 6},
    {(int[]){0, 5, 3, 1, 4, 2}, 6},
    {(int[]){0, 5, 3, 2, 1, 4}, 6},
    {(int[]){0, 5, 3, 2, 4, 1}, 6},
    {(int[]){0, 5, 3, 4, 1, 2}, 6},
    {(int[]){0, 5, 3, 4, 2, 1}, 6},
    {(int[]){0, 5, 4, 1, 2, 3}, 6},
    {(int[]){0, 5, 4, 1, 3, 2}, 6},
    {(int[]){0, 5, 4, 2, 1, 3}, 6},
    {(int[]){0, 5, 4, 2, 3, 1}, 6},
    {(int[]){0, 5, 4, 3, 1, 2}, 6},
    {(int[]){0, 5, 4, 3, 2, 1}, 6},
    {(int[]){1, 0, 2, 3, 4, 5}, 6},
    {(int[]){1, 0, 2, 3, 5, 4}, 6},
    {(int[]){1, 0, 2, 4, 3, 5}, 6},
    {(int[]){1, 0, 2, 4, 5, 3}, 6},
    {(int[]){1, 0, 2, 5, 3, 4}, 6},
    {(int[]){1, 0, 2, 5, 4, 3}, 6},
    {(int[]){1, 0, 3, 2, 4, 5}, 6},
    {(int[]){1, 0, 3, 2, 5, 4}, 6},
    {(int[]){1, 0, 3, 4, 2, 5}, 6},
    {(int[]){1, 0, 3, 4, 5, 2}, 6},
    {(int[]){1, 0, 3, 5, 2, 4}, 6},
    {(int[]){1, 0, 3, 5, 4, 2}, 6},
    {(int[]){1, 0, 4, 2, 3, 5}, 6},
    {(int[]){1, 0, 4, 2, 5, 3}, 6},
    {(int[]){1, 0, 4, 3, 2, 5}, 6},
    {(int[]){1, 0, 4, 3, 5, 2}, 6},
    {(int[]){1, 0, 4, 5, 2, 3}, 6},
    {(int[]){1, 0, 4, 5, 3, 2}, 6},
    {(int[]){1, 0, 5, 2, 3, 4}, 6},
    {(int[]){1, 0, 5, 2, 4, 3}, 6},
    {(int[]){1, 0, 5, 3, 2, 4}, 6},
    {(int[]){1, 0, 5, 3, 4, 2}, 6},
    {(int[]){1, 0, 5, 4, 2, 3}, 6},
    {(int[]){1, 0, 5, 4, 3, 2}, 6},
    {(int[]){1, 2, 0, 3, 4, 5}, 6},
    {(int[]){1, 2, 0, 3, 5, 4}, 6},
    {(int[]){1, 2, 0, 4, 3, 5}, 6},
    {(int[]){1, 2, 0, 4, 5, 3}, 6},
    {(int[]){1, 2, 0, 5, 3, 4}, 6},
    {(int[]){1, 2, 0, 5, 4, 3}, 6},
    {(int[]){1, 2, 3, 0, 4, 5}, 6},
    {(int[]){1, 2, 3, 0, 5, 4}, 6},
    {(int[]){1, 2, 3, 4, 0, 5}, 6},
    {(int[]){1, 2, 3, 4, 5, 0}, 6},
    {(int[]){1, 2, 3, 5, 0, 4}, 6},
    {(int[]){1, 2, 3, 5, 4, 0}, 6},
    {(int[]){1, 2, 4, 0, 3, 5}, 6},
    {(int[]){1, 2, 4, 0, 5, 3}, 6},
    {(int[]){1, 2, 4, 3, 0, 5}, 6},
    {(int[]){1, 2, 4, 3, 5, 0}, 6},
    {(int[]){1, 2, 4, 5, 0, 3}, 6},
    {(int[]){1, 2, 4, 5, 3, 0}, 6},
    {(int[]){1, 2, 5, 0, 3, 4}, 6},
    {(int[]){1, 2, 5, 0, 4, 3}, 6},
    {(int[]){1, 2, 5, 3, 0, 4}, 6},
    {(int[]){1, 2, 5, 3, 4, 0}, 6},
    {(int[]){1, 2, 5, 4, 0, 3}, 6},
    {(int[]){1, 2, 5, 4, 3, 0}, 6},
    {(int[]){1, 3, 0, 2, 4, 5}, 6},
    {(int[]){1, 3, 0, 2, 5, 4}, 6},
    {(int[]){1, 3, 0, 4, 2, 5}, 6},
    {(int[]){1, 3, 0, 4, 5, 2}, 6},
    {(int[]){1, 3, 0, 5, 2, 4}, 6},
    {(int[]){1, 3, 0, 5, 4, 2}, 6},
    {(int[]){1, 3, 2, 0, 4, 5}, 6},
    {(int[]){1, 3, 2, 0, 5, 4}, 6},
    {(int[]){1, 3, 2, 4, 0, 5}, 6},
    {(int[]){1, 3, 2, 4, 5, 0}, 6},
    {(int[]){1, 3, 2, 5, 0, 4}, 6},
    {(int[]){1, 3, 2, 5, 4, 0}, 6},
    {(int[]){1, 3, 4, 0, 2, 5}, 6},
    {(int[]){1, 3, 4, 0, 5, 2}, 6},
    {(int[]){1, 3, 4, 2, 0, 5}, 6},
    {(int[]){1, 3, 4, 2, 5, 0}, 6},
    {(int[]){1, 3, 4, 5, 0, 2}, 6},
    {(int[]){1, 3, 4, 5, 2, 0}, 6},
    {(int[]){1, 3, 5, 0, 2, 4}, 6},
    {(int[]){1, 3, 5, 0, 4, 2}, 6},
    {(int[]){1, 3, 5, 2, 0, 4}, 6},
    {(int[]){1, 3, 5, 2, 4, 0}, 6},
    {(int[]){1, 3, 5, 4, 0, 2}, 6},
    {(int[]){1, 3, 5, 4, 2, 0}, 6},
    {(int[]){1, 4, 0, 2, 3, 5}, 6},
    {(int[]){1, 4, 0, 2, 5, 3}, 6},
    {(int[]){1, 4, 0, 3, 2, 5}, 6},
    {(int[]){1, 4, 0, 3, 5, 2}, 6},
    {(int[]){1, 4, 0, 5, 2, 3}, 6},
    {(int[]){1, 4, 0, 5, 3, 2}, 6},
    {(int[]){1, 4, 2, 0, 3, 5}, 6},
    {(int[]){1, 4, 2, 0, 5, 3}, 6},
    {(int[]){1, 4, 2, 3, 0, 5}, 6},
    {(int[]){1, 4, 2, 3, 5, 0}, 6},
    {(int[]){1, 4, 2, 5, 0, 3}, 6},
    {(int[]){1, 4, 2, 5, 3, 0}, 6},
    {(int[]){1, 4, 3, 0, 2, 5}, 6},
    {(int[]){1, 4, 3, 0, 5, 2}, 6},
    {(int[]){1, 4, 3, 2, 0, 5}, 6},
    {(int[]){1, 4, 3, 2, 5, 0}, 6},
    {(int[]){1, 4, 3, 5, 0, 2}, 6},
    {(int[]){1, 4, 3, 5, 2, 0}, 6},
    {(int[]){1, 4, 5, 0, 2, 3}, 6},
    {(int[]){1, 4, 5, 0, 3, 2}, 6},
    {(int[]){1, 4, 5, 2, 0, 3}, 6},
    {(int[]){1, 4, 5, 2, 3, 0}, 6},
    {(int[]){1, 4, 5, 3, 0, 2}, 6},
    {(int[]){1, 4, 5, 3, 2, 0}, 6},
    {(int[]){1, 5, 0, 2, 3, 4}, 6},
    {(int[]){1, 5, 0, 2, 4, 3}, 6},
    {(int[]){1, 5, 0, 3, 2, 4}, 6},
    {(int[]){1, 5, 0, 3, 4, 2}, 6},
    {(int[]){1, 5, 0, 4, 2, 3}, 6},
    {(int[]){1, 5, 0, 4, 3, 2}, 6},
    {(int[]){1, 5, 2, 0, 3, 4}, 6},
    {(int[]){1, 5, 2, 0, 4, 3}, 6},
    {(int[]){1, 5, 2, 3, 0, 4}, 6},
    {(int[]){1, 5, 2, 3, 4, 0}, 6},
    {(int[]){1, 5, 2, 4, 0, 3}, 6},
    {(int[]){1, 5, 2, 4, 3, 0}, 6},
    {(int[]){1, 5, 3, 0, 2, 4}, 6},
    {(int[]){1, 5, 3, 0, 4, 2}, 6},
    {(int[]){1, 5, 3, 2, 0, 4}, 6},
    {(int[]){1, 5, 3, 2, 4, 0}, 6},
    {(int[]){1, 5, 3, 4, 0, 2}, 6},
    {(int[]){1, 5, 3, 4, 2, 0}, 6},
    {(int[]){1, 5, 4, 0, 2, 3}, 6},
    {(int[]){1, 5, 4, 0, 3, 2}, 6},
    {(int[]){1, 5, 4, 2, 0, 3}, 6},
    {(int[]){1, 5, 4, 2, 3, 0}, 6},
    {(int[]){1, 5, 4, 3, 0, 2}, 6},
    {(int[]){1, 5, 4, 3, 2, 0}, 6},
    {(int[]){2, 0, 1, 3, 4, 5}, 6},
    {(int[]){2, 0, 1, 3, 5, 4}, 6},
    {(int[]){2, 0, 1, 4, 3, 5}, 6},
    {(int[]){2, 0, 1, 4, 5, 3}, 6},
    {(int[]){2, 0, 1, 5, 3, 4}, 6},
    {(int[]){2, 0, 1, 5, 4, 3}, 6},
    {(int[]){2, 0, 3, 1, 4, 5}, 6},
    {(int[]){2, 0, 3, 1, 5, 4}, 6},
    {(int[]){2, 0, 3, 4, 1, 5}, 6},
    {(int[]){2, 0, 3, 4, 5, 1}, 6},
    {(int[]){2, 0, 3, 5, 1, 4}, 6},
    {(int[]){2, 0, 3, 5, 4, 1}, 6},
    {(int[]){2, 0, 4, 1, 3, 5}, 6},
    {(int[]){2, 0, 4, 1, 5, 3}, 6},
    {(int[]){2, 0, 4, 3, 1, 5}, 6},
    {(int[]){2, 0, 4, 3, 5, 1}, 6},
    {(int[]){2, 0, 4, 5, 1, 3}, 6},
    {(int[]){2, 0, 4, 5, 3, 1}, 6},
    {(int[]){2, 0, 5, 1, 3, 4}, 6},
    {(int[]){2, 0, 5, 1, 4, 3}, 6},
    {(int[]){2, 0, 5, 3, 1, 4}, 6},
    {(int[]){2, 0, 5, 3, 4, 1}, 6},
    {(int[]){2, 0, 5, 4, 1, 3}, 6},
    {(int[]){2, 0, 5, 4, 3, 1}, 6},
    {(int[]){2, 1, 0, 3, 4, 5}, 6},
    {(int[]){2, 1, 0, 3, 5, 4}, 6},
    {(int[]){2, 1, 0, 4, 3, 5}, 6},
    {(int[]){2, 1, 0, 4, 5, 3}, 6},
    {(int[]){2, 1, 0, 5, 3, 4}, 6},
    {(int[]){2, 1, 0, 5, 4, 3}, 6},
    {(int[]){2, 1, 3, 0, 4, 5}, 6},
    {(int[]){2, 1, 3, 0, 5, 4}, 6},
    {(int[]){2, 1, 3, 4, 0, 5}, 6},
    {(int[]){2, 1, 3, 4, 5, 0}, 6},
    {(int[]){2, 1, 3, 5, 0, 4}, 6},
    {(int[]){2, 1, 3, 5, 4, 0}, 6},
    {(int[]){2, 1, 4, 0, 3, 5}, 6},
    {(int[]){2, 1, 4, 0, 5, 3}, 6},
    {(int[]){2, 1, 4, 3, 0, 5}, 6},
    {(int[]){2, 1, 4, 3, 5, 0}, 6},
    {(int[]){2, 1, 4, 5, 0, 3}, 6},
    {(int[]){2, 1, 4, 5, 3, 0}, 6},
    {(int[]){2, 1, 5, 0, 3, 4}, 6},
    {(int[]){2, 1, 5, 0, 4, 3}, 6},
    {(int[]){2, 1, 5, 3, 0, 4}, 6},
    {(int[]){2, 1, 5, 3, 4, 0}, 6},
    {(int[]){2, 1, 5, 4, 0, 3}, 6},
    {(int[]){2, 1, 5, 4, 3, 0}, 6},
    {(int[]){2, 3, 0, 1, 4, 5}, 6},
    {(int[]){2, 3, 0, 1, 5, 4}, 6},
    {(int[]){2, 3, 0, 4, 1, 5}, 6},
    {(int[]){2, 3, 0, 4, 5, 1}, 6},
    {(int[]){2, 3, 0, 5, 1, 4}, 6},
    {(int[]){2, 3, 0, 5, 4, 1}, 6},
    {(int[]){2, 3, 1, 0, 4, 5}, 6},
    {(int[]){2, 3, 1, 0, 5, 4}, 6},
    {(int[]){2, 3, 1, 4, 0, 5}, 6},
    {(int[]){2, 3, 1, 4, 5, 0}, 6},
    {(int[]){2, 3, 1, 5, 0, 4}, 6},
    {(int[]){2, 3, 1, 5, 4, 0}, 6},
    {(int[]){2, 3, 4, 0, 1, 5}, 6},
    {(int[]){2, 3, 4, 0, 5, 1}, 6},
    {(int[]){2, 3, 4, 1, 0, 5}, 6},
    {(int[]){2, 3, 4, 1, 5, 0}, 6},
    {(int[]){2, 3, 4, 5, 0, 1}, 6},
    {(int[]){2, 3, 4, 5, 1, 0}, 6},
    {(int[]){2, 3, 5, 0, 1, 4}, 6},
    {(int[]){2, 3, 5, 0, 4, 1}, 6},
    {(int[]){2, 3, 5, 1, 0, 4}, 6},
    {(int[]){2, 3, 5, 1, 4, 0}, 6},
    {(int[]){2, 3, 5, 4, 0, 1}, 6},
    {(int[]){2, 3, 5, 4, 1, 0}, 6},
    {(int[]){2, 4, 0, 1, 3, 5}, 6},
    {(int[]){2, 4, 0, 1, 5, 3}, 6},
    {(int[]){2, 4, 0, 3, 1, 5}, 6},
    {(int[]){2, 4, 0, 3, 5, 1}, 6},
    {(int[]){2, 4, 0, 5, 1, 3}, 6},
    {(int[]){2, 4, 0, 5, 3, 1}, 6},
    {(int[]){2, 4, 1, 0, 3, 5}, 6},
    {(int[]){2, 4, 1, 0, 5, 3}, 6},
    {(int[]){2, 4, 1, 3, 0, 5}, 6},
    {(int[]){2, 4, 1, 3, 5, 0}, 6},
    {(int[]){2, 4, 1, 5, 0, 3}, 6},
    {(int[]){2, 4, 1, 5, 3, 0}, 6},
    {(int[]){2, 4, 3, 0, 1, 5}, 6},
    {(int[]){2, 4, 3, 0, 5, 1}, 6},
    {(int[]){2, 4, 3, 1, 0, 5}, 6},
    {(int[]){2, 4, 3, 1, 5, 0}, 6},
    {(int[]){2, 4, 3, 5, 0, 1}, 6},
    {(int[]){2, 4, 3, 5, 1, 0}, 6},
    {(int[]){2, 4, 5, 0, 1, 3}, 6},
    {(int[]){2, 4, 5, 0, 3, 1}, 6},
    {(int[]){2, 4, 5, 1, 0, 3}, 6},
    {(int[]){2, 4, 5, 1, 3, 0}, 6},
    {(int[]){2, 4, 5, 3, 0, 1}, 6},
    {(int[]){2, 4, 5, 3, 1, 0}, 6},
    {(int[]){2, 5, 0, 1, 3, 4}, 6},
    {(int[]){2, 5, 0, 1, 4, 3}, 6},
    {(int[]){2, 5, 0, 3, 1, 4}, 6},
    {(int[]){2, 5, 0, 3, 4, 1}, 6},
    {(int[]){2, 5, 0, 4, 1, 3}, 6},
    {(int[]){2, 5, 0, 4, 3, 1}, 6},
    {(int[]){2, 5, 1, 0, 3, 4}, 6},
    {(int[]){2, 5, 1, 0, 4, 3}, 6},
    {(int[]){2, 5, 1, 3, 0, 4}, 6},
    {(int[]){2, 5, 1, 3, 4, 0}, 6},
    {(int[]){2, 5, 1, 4, 0, 3}, 6},
    {(int[]){2, 5, 1, 4, 3, 0}, 6},
    {(int[]){2, 5, 3, 0, 1, 4}, 6},
    {(int[]){2, 5, 3, 0, 4, 1}, 6},
    {(int[]){2, 5, 3, 1, 0, 4}, 6},
    {(int[]){2, 5, 3, 1, 4, 0}, 6},
    {(int[]){2, 5, 3, 4, 0, 1}, 6},
    {(int[]){2, 5, 3, 4, 1, 0}, 6},
    {(int[]){2, 5, 4, 0, 1, 3}, 6},
    {(int[]){2, 5, 4, 0, 3, 1}, 6},
    {(int[]){2, 5, 4, 1, 0, 3}, 6},
    {(int[]){2, 5, 4, 1, 3, 0}, 6},
    {(int[]){2, 5, 4, 3, 0, 1}, 6},
    {(int[]){2, 5, 4, 3, 1, 0}, 6},
    {(int[]){3, 0, 1, 2, 4, 5}, 6},
    {(int[]){3, 0, 1, 2, 5, 4}, 6},
    {(int[]){3, 0, 1, 4, 2, 5}, 6},
    {(int[]){3, 0, 1, 4, 5, 2}, 6},
    {(int[]){3, 0, 1, 5, 2, 4}, 6},
    {(int[]){3, 0, 1, 5, 4, 2}, 6},
    {(int[]){3, 0, 2, 1, 4, 5}, 6},
    {(int[]){3, 0, 2, 1, 5, 4}, 6},
    {(int[]){3, 0, 2, 4, 1, 5}, 6},
    {(int[]){3, 0, 2, 4, 5, 1}, 6},
    {(int[]){3, 0, 2, 5, 1, 4}, 6},
    {(int[]){3, 0, 2, 5, 4, 1}, 6},
    {(int[]){3, 0, 4, 1, 2, 5}, 6},
    {(int[]){3, 0, 4, 1, 5, 2}, 6},
    {(int[]){3, 0, 4, 2, 1, 5}, 6},
    {(int[]){3, 0, 4, 2, 5, 1}, 6},
    {(int[]){3, 0, 4, 5, 1, 2}, 6},
    {(int[]){3, 0, 4, 5, 2, 1}, 6},
    {(int[]){3, 0, 5, 1, 2, 4}, 6},
    {(int[]){3, 0, 5, 1, 4, 2}, 6},
    {(int[]){3, 0, 5, 2, 1, 4}, 6},
    {(int[]){3, 0, 5, 2, 4, 1}, 6},
    {(int[]){3, 0, 5, 4, 1, 2}, 6},
    {(int[]){3, 0, 5, 4, 2, 1}, 6},
    {(int[]){3, 1, 0, 2, 4, 5}, 6},
    {(int[]){3, 1, 0, 2, 5, 4}, 6},
    {(int[]){3, 1, 0, 4, 2, 5}, 6},
    {(int[]){3, 1, 0, 4, 5, 2}, 6},
    {(int[]){3, 1, 0, 5, 2, 4}, 6},
    {(int[]){3, 1, 0, 5, 4, 2}, 6},
    {(int[]){3, 1, 2, 0, 4, 5}, 6},
    {(int[]){3, 1, 2, 0, 5, 4}, 6},
    {(int[]){3, 1, 2, 4, 0, 5}, 6},
    {(int[]){3, 1, 2, 4, 5, 0}, 6},
    {(int[]){3, 1, 2, 5, 0, 4}, 6},
    {(int[]){3, 1, 2, 5, 4, 0}, 6},
    {(int[]){3, 1, 4, 0, 2, 5}, 6},
    {(int[]){3, 1, 4, 0, 5, 2}, 6},
    {(int[]){3, 1, 4, 2, 0, 5}, 6},
    {(int[]){3, 1, 4, 2, 5, 0}, 6},
    {(int[]){3, 1, 4, 5, 0, 2}, 6},
    {(int[]){3, 1, 4, 5, 2, 0}, 6},
    {(int[]){3, 1, 5, 0, 2, 4}, 6},
    {(int[]){3, 1, 5, 0, 4, 2}, 6},
    {(int[]){3, 1, 5, 2, 0, 4}, 6},
    {(int[]){3, 1, 5, 2, 4, 0}, 6},
    {(int[]){3, 1, 5, 4, 0, 2}, 6},
    {(int[]){3, 1, 5, 4, 2, 0}, 6},
    {(int[]){3, 2, 0, 1, 4, 5}, 6},
    {(int[]){3, 2, 0, 1, 5, 4}, 6},
    {(int[]){3, 2, 0, 4, 1, 5}, 6},
    {(int[]){3, 2, 0, 4, 5, 1}, 6},
    {(int[]){3, 2, 0, 5, 1, 4}, 6},
    {(int[]){3, 2, 0, 5, 4, 1}, 6},
    {(int[]){3, 2, 1, 0, 4, 5}, 6},
    {(int[]){3, 2, 1, 0, 5, 4}, 6},
    {(int[]){3, 2, 1, 4, 0, 5}, 6},
    {(int[]){3, 2, 1, 4, 5, 0}, 6},
    {(int[]){3, 2, 1, 5, 0, 4}, 6},
    {(int[]){3, 2, 1, 5, 4, 0}, 6},
    {(int[]){3, 2, 4, 0, 1, 5}, 6},
    {(int[]){3, 2, 4, 0, 5, 1}, 6},
    {(int[]){3, 2, 4, 1, 0, 5}, 6},
    {(int[]){3, 2, 4, 1, 5, 0}, 6},
    {(int[]){3, 2, 4, 5, 0, 1}, 6},
    {(int[]){3, 2, 4, 5, 1, 0}, 6},
    {(int[]){3, 2, 5, 0, 1, 4}, 6},
    {(int[]){3, 2, 5, 0, 4, 1}, 6},
    {(int[]){3, 2, 5, 1, 0, 4}, 6},
    {(int[]){3, 2, 5, 1, 4, 0}, 6},
    {(int[]){3, 2, 5, 4, 0, 1}, 6},
    {(int[]){3, 2, 5, 4, 1, 0}, 6},
    {(int[]){3, 4, 0, 1, 2, 5}, 6},
    {(int[]){3, 4, 0, 1, 5, 2}, 6},
    {(int[]){3, 4, 0, 2, 1, 5}, 6},
    {(int[]){3, 4, 0, 2, 5, 1}, 6},
    {(int[]){3, 4, 0, 5, 1, 2}, 6},
    {(int[]){3, 4, 0, 5, 2, 1}, 6},
    {(int[]){3, 4, 1, 0, 2, 5}, 6},
    {(int[]){3, 4, 1, 0, 5, 2}, 6},
    {(int[]){3, 4, 1, 2, 0, 5}, 6},
    {(int[]){3, 4, 1, 2, 5, 0}, 6},
    {(int[]){3, 4, 1, 5, 0, 2}, 6},
    {(int[]){3, 4, 1, 5, 2, 0}, 6},
    {(int[]){3, 4, 2, 0, 1, 5}, 6},
    {(int[]){3, 4, 2, 0, 5, 1}, 6},
    {(int[]){3, 4, 2, 1, 0, 5}, 6},
    {(int[]){3, 4, 2, 1, 5, 0}, 6},
    {(int[]){3, 4, 2, 5, 0, 1}, 6},
    {(int[]){3, 4, 2, 5, 1, 0}, 6},
    {(int[]){3, 4, 5, 0, 1, 2}, 6},
    {(int[]){3, 4, 5, 0, 2, 1}, 6},
    {(int[]){3, 4, 5, 1, 0, 2}, 6},
    {(int[]){3, 4, 5, 1, 2, 0}, 6},
    {(int[]){3, 4, 5, 2, 0, 1}, 6},
    {(int[]){3, 4, 5, 2, 1, 0}, 6},
    {(int[]){3, 5, 0, 1, 2, 4}, 6},
    {(int[]){3, 5, 0, 1, 4, 2}, 6},
    {(int[]){3, 5, 0, 2, 1, 4}, 6},
    {(int[]){3, 5, 0, 2, 4, 1}, 6},
    {(int[]){3, 5, 0, 4, 1, 2}, 6},
    {(int[]){3, 5, 0, 4, 2, 1}, 6},
    {(int[]){3, 5, 1, 0, 2, 4}, 6},
    {(int[]){3, 5, 1, 0, 4, 2}, 6},
    {(int[]){3, 5, 1, 2, 0, 4}, 6},
    {(int[]){3, 5, 1, 2, 4, 0}, 6},
    {(int[]){3, 5, 1, 4, 0, 2}, 6},
    {(int[]){3, 5, 1, 4, 2, 0}, 6},
    {(int[]){3, 5, 2, 0, 1, 4}, 6},
    {(int[]){3, 5, 2, 0, 4, 1}, 6},
    {(int[]){3, 5, 2, 1, 0, 4}, 6},
    {(int[]){3, 5, 2, 1, 4, 0}, 6},
    {(int[]){3, 5, 2, 4, 0, 1}, 6},
    {(int[]){3, 5, 2, 4, 1, 0}, 6},
    {(int[]){3, 5, 4, 0, 1, 2}, 6},
    {(int[]){3, 5, 4, 0, 2, 1}, 6},
    {(int[]){3, 5, 4, 1, 0, 2}, 6},
    {(int[]){3, 5, 4, 1, 2, 0}, 6},
    {(int[]){3, 5, 4, 2, 0, 1}, 6},
    {(int[]){3, 5, 4, 2, 1, 0}, 6},
    {(int[]){4, 0, 1, 2, 3, 5}, 6},
    {(int[]){4, 0, 1, 2, 5, 3}, 6},
    {(int[]){4, 0, 1, 3, 2, 5}, 6},
    {(int[]){4, 0, 1, 3, 5, 2}, 6},
    {(int[]){4, 0, 1, 5, 2, 3}, 6},
    {(int[]){4, 0, 1, 5, 3, 2}, 6},
    {(int[]){4, 0, 2, 1, 3, 5}, 6},
    {(int[]){4, 0, 2, 1, 5, 3}, 6},
    {(int[]){4, 0, 2, 3, 1, 5}, 6},
    {(int[]){4, 0, 2, 3, 5, 1}, 6},
    {(int[]){4, 0, 2, 5, 1, 3}, 6},
    {(int[]){4, 0, 2, 5, 3, 1}, 6},
    {(int[]){4, 0, 3, 1, 2, 5}, 6},
    {(int[]){4, 0, 3, 1, 5, 2}, 6},
    {(int[]){4, 0, 3, 2, 1, 5}, 6},
    {(int[]){4, 0, 3, 2, 5, 1}, 6},
    {(int[]){4, 0, 3, 5, 1, 2}, 6},
    {(int[]){4, 0, 3, 5, 2, 1}, 6},
    {(int[]){4, 0, 5, 1, 2, 3}, 6},
    {(int[]){4, 0, 5, 1, 3, 2}, 6},
    {(int[]){4, 0, 5, 2, 1, 3}, 6},
    {(int[]){4, 0, 5, 2, 3, 1}, 6},
    {(int[]){4, 0, 5, 3, 1, 2}, 6},
    {(int[]){4, 0, 5, 3, 2, 1}, 6},
    {(int[]){4, 1, 0, 2, 3, 5}, 6},
    {(int[]){4, 1, 0, 2, 5, 3}, 6},
    {(int[]){4, 1, 0, 3, 2, 5}, 6},
    {(int[]){4, 1, 0, 3, 5, 2}, 6},
    {(int[]){4, 1, 0, 5, 2, 3}, 6},
    {(int[]){4, 1, 0, 5, 3, 2}, 6},
    {(int[]){4, 1, 2, 0, 3, 5}, 6},
    {(int[]){4, 1, 2, 0, 5, 3}, 6},
    {(int[]){4, 1, 2, 3, 0, 5}, 6},
    {(int[]){4, 1, 2, 3, 5, 0}, 6},
    {(int[]){4, 1, 2, 5, 0, 3}, 6},
    {(int[]){4, 1, 2, 5, 3, 0}, 6},
    {(int[]){4, 1, 3, 0, 2, 5}, 6},
    {(int[]){4, 1, 3, 0, 5, 2}, 6},
    {(int[]){4, 1, 3, 2, 0, 5}, 6},
    {(int[]){4, 1, 3, 2, 5, 0}, 6},
    {(int[]){4, 1, 3, 5, 0, 2}, 6},
    {(int[]){4, 1, 3, 5, 2, 0}, 6},
    {(int[]){4, 1, 5, 0, 2, 3}, 6},
    {(int[]){4, 1, 5, 0, 3, 2}, 6},
    {(int[]){4, 1, 5, 2, 0, 3}, 6},
    {(int[]){4, 1, 5, 2, 3, 0}, 6},
    {(int[]){4, 1, 5, 3, 0, 2}, 6},
    {(int[]){4, 1, 5, 3, 2, 0}, 6},
    {(int[]){4, 2, 0, 1, 3, 5}, 6},
    {(int[]){4, 2, 0, 1, 5, 3}, 6},
    {(int[]){4, 2, 0, 3, 1, 5}, 6},
    {(int[]){4, 2, 0, 3, 5, 1}, 6},
    {(int[]){4, 2, 0, 5, 1, 3}, 6},
    {(int[]){4, 2, 0, 5, 3, 1}, 6},
    {(int[]){4, 2, 1, 0, 3, 5}, 6},
    {(int[]){4, 2, 1, 0, 5, 3}, 6},
    {(int[]){4, 2, 1, 3, 0, 5}, 6},
    {(int[]){4, 2, 1, 3, 5, 0}, 6},
    {(int[]){4, 2, 1, 5, 0, 3}, 6},
    {(int[]){4, 2, 1, 5, 3, 0}, 6},
    {(int[]){4, 2, 3, 0, 1, 5}, 6},
    {(int[]){4, 2, 3, 0, 5, 1}, 6},
    {(int[]){4, 2, 3, 1, 0, 5}, 6},
    {(int[]){4, 2, 3, 1, 5, 0}, 6},
    {(int[]){4, 2, 3, 5, 0, 1}, 6},
    {(int[]){4, 2, 3, 5, 1, 0}, 6},
    {(int[]){4, 2, 5, 0, 1, 3}, 6},
    {(int[]){4, 2, 5, 0, 3, 1}, 6},
    {(int[]){4, 2, 5, 1, 0, 3}, 6},
    {(int[]){4, 2, 5, 1, 3, 0}, 6},
    {(int[]){4, 2, 5, 3, 0, 1}, 6},
    {(int[]){4, 2, 5, 3, 1, 0}, 6},
    {(int[]){4, 3, 0, 1, 2, 5}, 6},
    {(int[]){4, 3, 0, 1, 5, 2}, 6},
    {(int[]){4, 3, 0, 2, 1, 5}, 6},
    {(int[]){4, 3, 0, 2, 5, 1}, 6},
    {(int[]){4, 3, 0, 5, 1, 2}, 6},
    {(int[]){4, 3, 0, 5, 2, 1}, 6},
    {(int[]){4, 3, 1, 0, 2, 5}, 6},
    {(int[]){4, 3, 1, 0, 5, 2}, 6},
    {(int[]){4, 3, 1, 2, 0, 5}, 6},
    {(int[]){4, 3, 1, 2, 5, 0}, 6},
    {(int[]){4, 3, 1, 5, 0, 2}, 6},
    {(int[]){4, 3, 1, 5, 2, 0}, 6},
    {(int[]){4, 3, 2, 0, 1, 5}, 6},
    {(int[]){4, 3, 2, 0, 5, 1}, 6},
    {(int[]){4, 3, 2, 1, 0, 5}, 6},
    {(int[]){4, 3, 2, 1, 5, 0}, 6},
    {(int[]){4, 3, 2, 5, 0, 1}, 6},
    {(int[]){4, 3, 2, 5, 1, 0}, 6},
    {(int[]){4, 3, 5, 0, 1, 2}, 6},
    {(int[]){4, 3, 5, 0, 2, 1}, 6},
    {(int[]){4, 3, 5, 1, 0, 2}, 6},
    {(int[]){4, 3, 5, 1, 2, 0}, 6},
    {(int[]){4, 3, 5, 2, 0, 1}, 6},
    {(int[]){4, 3, 5, 2, 1, 0}, 6},
    {(int[]){4, 5, 0, 1, 2, 3}, 6},
    {(int[]){4, 5, 0, 1, 3, 2}, 6},
    {(int[]){4, 5, 0, 2, 1, 3}, 6},
    {(int[]){4, 5, 0, 2, 3, 1}, 6},
    {(int[]){4, 5, 0, 3, 1, 2}, 6},
    {(int[]){4, 5, 0, 3, 2, 1}, 6},
    {(int[]){4, 5, 1, 0, 2, 3}, 6},
    {(int[]){4, 5, 1, 0, 3, 2}, 6},
    {(int[]){4, 5, 1, 2, 0, 3}, 6},
    {(int[]){4, 5, 1, 2, 3, 0}, 6},
    {(int[]){4, 5, 1, 3, 0, 2}, 6},
    {(int[]){4, 5, 1, 3, 2, 0}, 6},
    {(int[]){4, 5, 2, 0, 1, 3}, 6},
    {(int[]){4, 5, 2, 0, 3, 1}, 6},
    {(int[]){4, 5, 2, 1, 0, 3}, 6},
    {(int[]){4, 5, 2, 1, 3, 0}, 6},
    {(int[]){4, 5, 2, 3, 0, 1}, 6},
    {(int[]){4, 5, 2, 3, 1, 0}, 6},
    {(int[]){4, 5, 3, 0, 1, 2}, 6},
    {(int[]){4, 5, 3, 0, 2, 1}, 6},
    {(int[]){4, 5, 3, 1, 0, 2}, 6},
    {(int[]){4, 5, 3, 1, 2, 0}, 6},
    {(int[]){4, 5, 3, 2, 0, 1}, 6},
    {(int[]){4, 5, 3, 2, 1, 0}, 6},
    {(int[]){5, 0, 1, 2, 3, 4}, 6},
    {(int[]){5, 0, 1, 2, 4, 3}, 6},
    {(int[]){5, 0, 1, 3, 2, 4}, 6},
    {(int[]){5, 0, 1, 3, 4, 2}, 6},
    {(int[]){5, 0, 1, 4, 2, 3}, 6},
    {(int[]){5, 0, 1, 4, 3, 2}, 6},
    {(int[]){5, 0, 2, 1, 3, 4}, 6},
    {(int[]){5, 0, 2, 1, 4, 3}, 6},
    {(int[]){5, 0, 2, 3, 1, 4}, 6},
    {(int[]){5, 0, 2, 3, 4, 1}, 6},
    {(int[]){5, 0, 2, 4, 1, 3}, 6},
    {(int[]){5, 0, 2, 4, 3, 1}, 6},
    {(int[]){5, 0, 3, 1, 2, 4}, 6},
    {(int[]){5, 0, 3, 1, 4, 2}, 6},
    {(int[]){5, 0, 3, 2, 1, 4}, 6},
    {(int[]){5, 0, 3, 2, 4, 1}, 6},
    {(int[]){5, 0, 3, 4, 1, 2}, 6},
    {(int[]){5, 0, 3, 4, 2, 1}, 6},
    {(int[]){5, 0, 4, 1, 2, 3}, 6},
    {(int[]){5, 0, 4, 1, 3, 2}, 6},
    {(int[]){5, 0, 4, 2, 1, 3}, 6},
    {(int[]){5, 0, 4, 2, 3, 1}, 6},
    {(int[]){5, 0, 4, 3, 1, 2}, 6},
    {(int[]){5, 0, 4, 3, 2, 1}, 6},
    {(int[]){5, 1, 0, 2, 3, 4}, 6},
    {(int[]){5, 1, 0, 2, 4, 3}, 6},
    {(int[]){5, 1, 0, 3, 2, 4}, 6},
    {(int[]){5, 1, 0, 3, 4, 2}, 6},
    {(int[]){5, 1, 0, 4, 2, 3}, 6},
    {(int[]){5, 1, 0, 4, 3, 2}, 6},
    {(int[]){5, 1, 2, 0, 3, 4}, 6},
    {(int[]){5, 1, 2, 0, 4, 3}, 6},
    {(int[]){5, 1, 2, 3, 0, 4}, 6},
    {(int[]){5, 1, 2, 3, 4, 0}, 6},
    {(int[]){5, 1, 2, 4, 0, 3}, 6},
    {(int[]){5, 1, 2, 4, 3, 0}, 6},
    {(int[]){5, 1, 3, 0, 2, 4}, 6},
    {(int[]){5, 1, 3, 0, 4, 2}, 6},
    {(int[]){5, 1, 3, 2, 0, 4}, 6},
    {(int[]){5, 1, 3, 2, 4, 0}, 6},
    {(int[]){5, 1, 3, 4, 0, 2}, 6},
    {(int[]){5, 1, 3, 4, 2, 0}, 6},
    {(int[]){5, 1, 4, 0, 2, 3}, 6},
    {(int[]){5, 1, 4, 0, 3, 2}, 6},
    {(int[]){5, 1, 4, 2, 0, 3}, 6},
    {(int[]){5, 1, 4, 2, 3, 0}, 6},
    {(int[]){5, 1, 4, 3, 0, 2}, 6},
    {(int[]){5, 1, 4, 3, 2, 0}, 6},
    {(int[]){5, 2, 0, 1, 3, 4}, 6},
    {(int[]){5, 2, 0, 1, 4, 3}, 6},
    {(int[]){5, 2, 0, 3, 1, 4}, 6},
    {(int[]){5, 2, 0, 3, 4, 1}, 6},
    {(int[]){5, 2, 0, 4, 1, 3}, 6},
    {(int[]){5, 2, 0, 4, 3, 1}, 6},
    {(int[]){5, 2, 1, 0, 3, 4}, 6},
    {(int[]){5, 2, 1, 0, 4, 3}, 6},
    {(int[]){5, 2, 1, 3, 0, 4}, 6},
    {(int[]){5, 2, 1, 3, 4, 0}, 6},
    {(int[]){5, 2, 1, 4, 0, 3}, 6},
    {(int[]){5, 2, 1, 4, 3, 0}, 6},
    {(int[]){5, 2, 3, 0, 1, 4}, 6},
    {(int[]){5, 2, 3, 0, 4, 1}, 6},
    {(int[]){5, 2, 3, 1, 0, 4}, 6},
    {(int[]){5, 2, 3, 1, 4, 0}, 6},
    {(int[]){5, 2, 3, 4, 0, 1}, 6},
    {(int[]){5, 2, 3, 4, 1, 0}, 6},
    {(int[]){5, 2, 4, 0, 1, 3}, 6},
    {(int[]){5, 2, 4, 0, 3, 1}, 6},
    {(int[]){5, 2, 4, 1, 0, 3}, 6},
    {(int[]){5, 2, 4, 1, 3, 0}, 6},
    {(int[]){5, 2, 4, 3, 0, 1}, 6},
    {(int[]){5, 2, 4, 3, 1, 0}, 6},
    {(int[]){5, 3, 0, 1, 2, 4}, 6},
    {(int[]){5, 3, 0, 1, 4, 2}, 6},
    {(int[]){5, 3, 0, 2, 1, 4}, 6},
    {(int[]){5, 3, 0, 2, 4, 1}, 6},
    {(int[]){5, 3, 0, 4, 1, 2}, 6},
    {(int[]){5, 3, 0, 4, 2, 1}, 6},
    {(int[]){5, 3, 1, 0, 2, 4}, 6},
    {(int[]){5, 3, 1, 0, 4, 2}, 6},
    {(int[]){5, 3, 1, 2, 0, 4}, 6},
    {(int[]){5, 3, 1, 2, 4, 0}, 6},
    {(int[]){5, 3, 1, 4, 0, 2}, 6},
    {(int[]){5, 3, 1, 4, 2, 0}, 6},
    {(int[]){5, 3, 2, 0, 1, 4}, 6},
    {(int[]){5, 3, 2, 0, 4, 1}, 6},
    {(int[]){5, 3, 2, 1, 0, 4}, 6},
    {(int[]){5, 3, 2, 1, 4, 0}, 6},
    {(int[]){5, 3, 2, 4, 0, 1}, 6},
    {(int[]){5, 3, 2, 4, 1, 0}, 6},
    {(int[]){5, 3, 4, 0, 1, 2}, 6},
    {(int[]){5, 3, 4, 0, 2, 1}, 6},
    {(int[]){5, 3, 4, 1, 0, 2}, 6},
    {(int[]){5, 3, 4, 1, 2, 0}, 6},
    {(int[]){5, 3, 4, 2, 0, 1}, 6},
    {(int[]){5, 3, 4, 2, 1, 0}, 6},
    {(int[]){5, 4, 0, 1, 2, 3}, 6},
    {(int[]){5, 4, 0, 1, 3, 2}, 6},
    {(int[]){5, 4, 0, 2, 1, 3}, 6},
    {(int[]){5, 4, 0, 2, 3, 1}, 6},
    {(int[]){5, 4, 0, 3, 1, 2}, 6},
    {(int[]){5, 4, 0, 3, 2, 1}, 6},
    {(int[]){5, 4, 1, 0, 2, 3}, 6},
    {(int[]){5, 4, 1, 0, 3, 2}, 6},
    {(int[]){5, 4, 1, 2, 0, 3}, 6},
    {(int[]){5, 4, 1, 2, 3, 0}, 6},
    {(int[]){5, 4, 1, 3, 0, 2}, 6},
    {(int[]){5, 4, 1, 3, 2, 0}, 6},
    {(int[]){5, 4, 2, 0, 1, 3}, 6},
    {(int[]){5, 4, 2, 0, 3, 1}, 6},
    {(int[]){5, 4, 2, 1, 0, 3}, 6},
    {(int[]){5, 4, 2, 1, 3, 0}, 6},
    {(int[]){5, 4, 2, 3, 0, 1}, 6},
    {(int[]){5, 4, 2, 3, 1, 0}, 6},
    {(int[]){5, 4, 3, 0, 1, 2}, 6},
    {(int[]){5, 4, 3, 0, 2, 1}, 6},
    {(int[]){5, 4, 3, 1, 0, 2}, 6},
    {(int[]){5, 4, 3, 1, 2, 0}, 6},
    {(int[]){5, 4, 3, 2, 0, 1}, 6},
    {(int[]){5, 4, 3, 2, 1, 0}, 6},
    {(int[]){10, 7, 23, 12, -12, 0, 100, 7, 23, 72, 100, 6, 8, 9, 12, 20, 100, 122,
             12, 31, 12, 11, -23, -21, 12, 44, 86, 12, 41, 0, 2, 3, 4, 5, 10, 1000,
             1001, 1002, 1003, 1004}, 40},
};

int test_sort(const char* prefix) {
    UNUSED(prefix);

    struct namedFunc {
        char* name;
        sort_fn fn;
    };

    struct namedFunc fns[] = {
        {"sort_bubble", sort_bubble},
        {"sort_merge_nspace", sort_merge_nspace},
    };
    int nfns = sizeof(fns) / sizeof(struct namedFunc);

    int i;
    int fail;
    for (i=0; i<nfns; i++) {
        fail = test_sort_fn(fns[i].fn, fns[i].name);
        if (fail) {
            return fail;
        }
    }

    return 0;
}

int test_sort_fn(sort_fn fn, const char* prefix) {
    int ntests = sizeof(tests) / sizeof(array);

    int i;
    array *input, *backup;
    int* obtained;
    for (i=0; i<ntests; i++) {
        input = array_clone(&tests[i]);
        if (! input) {
            return 1;
        }

        backup = array_clone(input);
        if (! backup) {
            array_free(input);
            return 1;
        }

        printf("testing \"%s\": test %d:\n", prefix, i);
        char* ss = to_str(input->a, input->n);
        printf("\t\t   input: %s\n", ss);
        free(ss);

        obtained = fn(input->a, input->n);
        if (!is_sorted(obtained, input->n)) {
            printf("testing \"%s\": test %d failed:\n", prefix, i);
            printf("\tresult is not sorted:\n");

            char* s = to_str(backup->a, backup->n);
            printf("\t\t   input: %s\n", s);
            free(s);

            s = to_str(obtained, input->n);
            printf("\t\tobtained: %s\n", s);
            free(s);

            array_free(backup);
            array_free(input);
            return 2;
        }

        char* s = to_str(obtained, input->n);
        printf("\t\tobtained: %s\n", s);
        free(s);

        array_free(backup);
        array_free(input);
    }

    return 0;
}

array* array_new(int* a, int n) {
    array* new = (array*) malloc(sizeof(array));
    if (! new) {
        return NULL;
    }

    new->n = n;

    new->a = (int*) malloc(n * sizeof(int));
    if (! new->a) {
        free(new);
        return NULL;
    }

    memcpy(new->a, a, n*sizeof(int));

    return new;
}

array* array_clone(array* a) {
    return array_new(a->a, a->n);
}

void array_free(array* a) {
    free(a->a);
    free(a);
}

int is_sorted(int* a, int n) {
    if (a == NULL || n == 0) {
        return 1;
    }

    int i;
    for (i=1; i<n; i++) {
        if (a[i] < a[i-1]) {
            return 0;
        }
    }

    return 1;
}

