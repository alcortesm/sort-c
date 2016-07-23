#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

void _sort_merge_nspace(int* dst, int* src, int f, int n);
void merge(int* dst, int* src, int a, int b, int c, int d);

int* sort_merge_nspace(int* src, int n) {
    if (n==0) {
        return NULL;
    }

    int* dst = (int*) malloc(n * sizeof(int));
    if (! dst) {
        return NULL;
    }

    if (n==1) {
        return memcpy(dst, src, sizeof(int));
    }

    _sort_merge_nspace(dst, src, 0, n);
    return dst;
}

void _sort_merge_nspace(int* dst, int* src, int b, int e) {
    printf("_sort_merge_nspace[%d:%d]\n", b, e);

    int sz = e-b;
    if (sz==1) {
        return;
    }

    _sort_merge_nspace(dst, src, b, b+sz/2);
    _sort_merge_nspace(dst, src, b+sz/2, e);
    merge(dst, src, b, b+(sz/2), b+(sz/2), e);
}

void merge(int* dst, int* src, int ab, int ae, int bb, int be) {
    printf("merge [%d:%d] and [%d:%d]\n", ab, ae, bb, be);
    int* a = src+ab;
    int* b = src+bb;
    int i = 0;
    for (;;) {
        if (a >= src+ae) {
            memcpy(dst+i, b, b-src+be);
            return;
        }
        if (b >= src+be) {
            memcpy(dst+i, a, a-src+ae);
            return;
        }
        if (*a <= *b) {
            dst[i++] = *a;
            a++;
        } else {
            dst[i++] = *b;
            b++;
        }
    }
}
