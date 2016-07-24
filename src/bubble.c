#include "array.h"

void swap(int*a, int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

void sort_bubble(array* a) {
    if (! a) {
        return;
    }

    if (array_size(a) < 2) {
        return;
    }

    int limit;
    int sorted_since;
    for (limit=array_size(a); limit>1; limit--) {
        sorted_since = -1;
        int i;
        for (i=1; i<limit; i++) {
            if (a->a[i] < a->a[i-1]) {
                swap(a->a, i, i-1);
                sorted_since = -1;
            } else if (sorted_since == -1) {
                sorted_since = i-1;
            }
        }

        if (sorted_since != -1) {
            limit = sorted_since + 1;
            // +1 to account for the outer loop afterthought
        }
    }

    return;
}
