#include <stdlib.h>
#include <stdio.h>

#include "util.h"

void swap(int*a, int i, int j) {
    int tmp = a[i];
    a[i] = a[j];
    a[j] = tmp;
}

int* sort_bubble(int* a, int n) {
    if (a == NULL || n == 0) {
        return NULL;
    }

    if (n == 1) {
        return a;
    }

    int limit;
    int sorted_since;
    for (limit=n; limit>1; limit--) {
        sorted_since = -1;
        int i;
        for (i=1; i<limit; i++) {
            if (a[i] < a[i-1]) {
                swap(a, i, i-1);
                sorted_since = -1;
            } else if (sorted_since == -1) {
                sorted_since = i-1;
            }
        }

        if (sorted_since != -1) {
            limit = sorted_since + 1; // +1 to account for the outer loop afterthought
        }
    }

    return a;
}
