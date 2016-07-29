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
    int* r1 = src+ab;
    int* r2 = src+bb;
    int i = ab;
    for (;;) {
        if (r1 >= src+ae) {
            memcpy(tmp+i, r2, (src+be-r2)*sizeof(int));
            break;
        }
        if (r2 >= src+be) {
            memcpy(tmp+i, r1, (src+ae-r1)*sizeof(int));
            break;
        }
        if (*r1 <= *r2) {
            tmp[i++] = *r1;
            r1++;
        } else {
            tmp[i++] = *r2;
            r2++;
        }
    }
    memcpy(src+ab, tmp+ab, (be-ab)*sizeof(int));
}
