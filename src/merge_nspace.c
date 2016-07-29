#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "array.h"

void _sort_merge_nspace(int* dst, int* src, int f, int n);
void merge(int* dst, int* src, int b, int e);

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
    merge(tmp, src, b, e);
}

// merge rearranges the ints in the src array, from b up to, but not
// including, e.
//
// Think of the array as two imaginary queues, one from b to the middle
// element and another from the middle element to e.
//
// The smallest int from the head of each queue is dequeued and queued
// into a temporal array, until both queues are empty.  Then the
// contents of the temporal array are copied back into the original
// array.
void merge(int* tmp, int* src, int b, int e) {
    int m = b + (e-b)/2;
    int* h1 = src+b;
    int* h2 = src+m;
    int i = b;
    for (;;) {
        if (h1 >= src+m) {
            memcpy(tmp+i, h2, (src+e-h2)*sizeof(int));
            break;
        }
        if (h2 >= src+e) {
            memcpy(tmp+i, h1, (src+m-h1)*sizeof(int));
            break;
        }
        if (*h1 <= *h2) {
            tmp[i++] = *h1;
            h1++;
        } else {
            tmp[i++] = *h2;
            h2++;
        }
    }
    memcpy(src+b, tmp+b, (e-b)*sizeof(int));
}
