#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sort.h>

#include "util.h"


typedef struct {
    int* a;
    int n;
} array;

array* array_new(array* a) {
    array* new = (array*) malloc(sizeof(array));
    if (! new) {
        return NULL;
    }

    new->n = a->n;

    new->a = (int*) malloc(a->n * sizeof(int));
    if (! new->a) {
        free(new);
        return NULL;
    }

    memcpy(new->a, a->a, a->n*sizeof(int));

    return new;
}

void array_free(array* a) {
    free(a->a);
    free(a);
}

int is_sorted(int* a, int n);

int test_sort(const char* prefix) {
    UNUSED(prefix);

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
    };
    int ntests = sizeof(tests) / sizeof(array);

    int i;
    array input, *backup;
    int* obtained;
    for (i=0; i<ntests; i++) {
        input = tests[i];
        backup = array_new(&input);
        if (! backup) {
            return 1;
        }

        obtained = sort_bubble(input.a, input.n);
        if (!is_sorted(obtained, input.n)) {
            printf("test_sort -> sort_bubble: test %d failed:\n", i);
            printf("\tresult is not sorted:\n");

            char* s = to_str(backup->a, backup->n);
            printf("\t\t   input: %s\n", s);
            free(s);

            s = to_str(obtained, input.n);
            printf("\t\tobtained: %s\n", s);
            free(s);

            array_free(backup);
            return 2;
        }

        array_free(backup);
    }

    return 1;
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
