#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "array.h"

void split_and_merge(int* tmp, int* src, int n);
void merge(int* tmp, int* src, int n);

int sort_merge_nspace(array* a) {
    if (! a) {
        return 1;
    }

    int sz = array_size(a);
    if (sz < 2) {
        return 0;
    }

    int* tmp = malloc(sz * sizeof(int));
    if (! tmp) {
        perror("malloc");
        return 1;
    }

    split_and_merge(tmp, a->a, sz);

    free(tmp);

    return 0;
}

// sorts the first n elements of src by splitting the array at the
// middle, recursively sorting each part and merging the two sorted
// parts taking care to keep the result sorted.
void split_and_merge(int* tmp, int* src, int n) {
    if (n == 1) {
        return;
    }

    int first_half = n/2;
    int last_half  = first_half + n%2;

    split_and_merge(tmp, src,            first_half);
    split_and_merge(tmp, src+first_half, last_half);

    merge(tmp, src, n);
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
