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
    for (limit=n; limit>1; limit--) {
        int i;
        for (i=1; i<limit; i++) {
            char* s = to_str(a, n);
            printf("i=%d limit=%d array=%s\n", i, limit, s);
            free(s);

            if (a[i] < a[i-1]) {
                swap(a, i, i-1);
                printf("    swap %d and %d\n", a[i], a[i-1]);
            }
        }
    }

    return a;
}
