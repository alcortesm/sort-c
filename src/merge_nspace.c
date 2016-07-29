#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "array.h"

void _sort_merge_nspace(int* dst, int* src, int f, int n);
void merge(int* dst, int* src, int a, int b, int c, int d);

int sort_merge_nspace(array* a) {
    int sz = array_size(a);
    if (sz<2) {
        return 0;
    }

    int* dst = (int*) malloc(sz * sizeof(int));
    if (! dst) {
        perror("malloc");
        return 1;
    }

    _sort_merge_nspace(dst, a->a, 0, sz);
    free(dst);

    return 0;
}

void _sort_merge_nspace(int* dst, int* src, int b, int e) {
    int sz = e-b;
    if (sz==1) {
        return;
    }

    _sort_merge_nspace(dst, src, b, b+sz/2);
    _sort_merge_nspace(dst, src, b+sz/2, e);
    merge(dst, src, b, b+sz/2, b+sz/2, e);
}

void merge(int* dst, int* src, int ab, int ae, int bb, int be) {
    int* a = src+ab;
    int* b = src+bb;
    int i = ab;
    for (;;) {
        if (a >= src+ae) {
            memcpy(dst+i, b, (src+be-b)*sizeof(int));
            break;
        }
        if (b >= src+be) {
            memcpy(dst+i, a, (src+ae-a)*sizeof(int));
            break;
        }
        if (*a <= *b) {
            dst[i++] = *a;
            a++;
        } else {
            dst[i++] = *b;
            b++;
        }
    }
    memcpy(src+ab, dst+ab, (be-ab)*sizeof(int));
}
