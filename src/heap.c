#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "array.h"

void heapify(array* a);
void siftdown(array* a, int start, int end);
int parent(int i);
int left(int i);

int sort_heap(array* a) {
    if (! a) {
        return 1;
    }

    heapify(a);

    int last = array_size(a) - 1;
    while (last > 0) {
        array_swap(a, 0, last);
        last--;
        siftdown(a, 0, last);
    }

    return 0;
}

// rearrange the elements in the array as if it were a max heap.
void heapify(array* a) {
    const int last = array_size(a)-1;
    int start = parent(last);

    while(start >= 0) {
        siftdown(a, start, last);
        start--;
    }
}

// repair a max heap tree with its root at `root`, assuming the childs
// are already repaired.
void siftdown(array* a, int start, int end) {
    int root = start;

    int child, swap;
    while(left(root) <= end) {
        child = left(root);
        swap = root;

        if (a->a[swap] < a->a[child]) {
            swap = child;
        }

        if (child+1 <= end && a->a[swap]< a->a[child+1]) {
            swap = child + 1;
        }

        if (swap == root) {
            return;
        }
        array_swap(a, root, swap);
        root = swap;
    }
}


int parent(int i) {
    return i/2;
}

int left(int i) {
    return 2*i;
}
