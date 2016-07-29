#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "array.h"

void split_and_merge(int* tmp, int* src, int begin, int end);
void merge(int* tmp, int* src, int n);

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

    split_and_merge(tmp, a->a, 0, sz);

    free(tmp);

    return 0;
}

// sorts the numbers from src+b to src+e (not included) by splitting
// the array in the middle, recursively sorting each part and merging
// the two sorted parts into a single one.
void split_and_merge(int* tmp, int* src, int b, int e) {
    int sz = e-b;
    if (sz==1) {
        return;
    }

    int mid = b+sz/2;
    split_and_merge(tmp, src, b, mid);
    split_and_merge(tmp, src, mid, e);
    merge(tmp+b, src+b, sz);
}

// merge rearranges the first n elements of src.
//
// Think of src as two imaginary queues, one from the beginning of src
// to its middle element and another from its middle element to the n-1
// one.
//
// The smallest int from the head of each queue is dequeued and queued
// into a temporal array, until both queues are empty.
//
// Then the contents of the temporal array are copied back into the
// original array.
void merge(int* tmp, int* src, int n) {
    int* const mid = src + n/2;
    int* const end = src + n;

    int* h1 = src;    // head of first queue
    int* h2 = mid;    // head of second queue
    int* next = tmp;  // next free place in the output queue

    for (;;) {
        if (h1 >= mid) {
            memcpy(next, h2, (end-h2)*sizeof(int));
            break;
        }
        if (h2 >= end) {
            memcpy(next, h1, (mid-h1)*sizeof(int));
            break;
        }
        if (*h1 <= *h2) {
            *next = *h1;
            h1++;
        } else {
            *next = *h2;
            h2++;
        }
        next++;
    }

    memcpy(src, tmp, n*sizeof(int));
}
