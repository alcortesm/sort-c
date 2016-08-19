#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "array.h"

void quick(array* a, int b, int e);
int choose_pivot(array* a, int b, int e);
int partition(array* a, int l, int r, int p);

int sort_quick(array* a) {
    if (! a) {
        return 1;
    }

    int sz = array_size(a);
    if (sz < 2) {
        return 0;
    }

    quick(a, 0, sz-1);

    return 0;
}

void quick(array* a, int b, int e) {
    int sz = e - b + 1;
    if (sz < 2) {
        return;
    }

    int p = choose_pivot(a, b, e);
    p = partition(a, b, e, p);
    quick(a, b, p-1);
    quick(a, p+1, e);
}

int choose_pivot(array* a, int b, int e) {
    // simple implementation
    UNUSED(a);
    UNUSED(b);
    return e;
}

int partition(array* a, int l, int r, int p) {
    for (;l != r ;) {
        if (a->a[l] <= a->a[p]) {
            l++;
            continue;
        }
        if (r == p) {
            r--;
            continue;
        }
        if (a->a[r] >= a->a[p]) {
            r--;
            continue;
        }
        array_swap(a, l, r);
    }

    array_swap(a, l, p);

    return l;
}
