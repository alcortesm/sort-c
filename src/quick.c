#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "array.h"

void quick(array* a, int b, int e);
int partition(array* a, int l, int r);

int sort_quick(array* a) {
    if (! a) {
        return 1;
    }

    int sz = array_size(a);
    quick(a, 0, sz-1);

    return 0;
}

void quick(array* a, int b, int e) {
    int sz = e - b + 1;
    if (sz < 2) {
        return;
    }

    if (sz == 2) {
        if (a->a[b] > a->a[e]) {
            array_swap(a, b, e);
            return;
        }
        return;
    }

    int p = partition(a, b, e);
    quick(a, b, p-1);
    quick(a, p+1, e);
}

int partition(array* a, int l, int r) {
    int p = r;
    while (l != r) {
        if (a->a[l] <= a->a[p]) {
            l++;
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
