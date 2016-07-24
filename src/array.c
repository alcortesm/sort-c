#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "util.h"

array* array_new(int* a, int n) {
    if (! a && n != 0) {
        return NULL;
    }

    if (n < 0) {
        return NULL;
    }

    array* new = (array*) malloc(sizeof(array));
    if (! new) {
        return NULL;
    }

    if (! a) {
        new->a = NULL;
        new->n = 0;
        return new;
    }

    new->a = (int*) malloc(n*sizeof(int));
    if (! new->a) {
        free(new);
        return NULL;
    }

    memcpy(new->a, a, n*sizeof(int));
    new->n = n;
    return new;
}

array* array_clone(array* a) {
    return array_new(a->a, a->n);
}

void array_free(array* a) {
    if (a->a) {
        free(a->a);
    }
    free(a);
}

int array_size(array* a) {
    return a->n;
}

char* array_to_str(array* a) {
    if (! a) {
        return NULL;
    }

    return to_str(a->a, a->n);
}

int array_equals(array* a, array* b) {
    if (a->n != b->n) {
        return 0;
    }

    int i;
    for (i=0; i<a->n; i++) {
        if (a->a[i] != b->a[i]) {
            return 0;
        }
    }

    return 1;
}
