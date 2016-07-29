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

    int* tmp = (int*) malloc(sz * sizeof(int));
    if (! tmp) {
        perror("malloc");
        return 1;
    }

    _sort_merge_nspace(tmp, a->a, 0, sz);
    free(tmp);

    return 0;
}

void _sort_merge_nspace(int* tmp, int* src, int b, int e) {
    int sz = e-b;
    if (sz==1) {
        return;
    }

    _sort_merge_nspace(tmp, src, b, b+sz/2);
    _sort_merge_nspace(tmp, src, b+sz/2, e);
    merge(tmp, src, b, b+sz/2, b+sz/2, e);
}

void merge(int* tmp, int* src, int ab, int ae, int bb, int be) {
    int* a = src+ab;
    int* b = src+bb;
    int i = ab;
    for (;;) {
        if (a >= src+ae) {
            memcpy(tmp+i, b, (src+be-b)*sizeof(int));
            break;
        }
        if (b >= src+be) {
            memcpy(tmp+i, a, (src+ae-a)*sizeof(int));
            break;
        }
        if (*a <= *b) {
            tmp[i++] = *a;
            a++;
        } else {
            tmp[i++] = *b;
            b++;
        }
    }
    memcpy(src+ab, tmp+ab, (be-ab)*sizeof(int));
}
