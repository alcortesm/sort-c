#include "array.h"

int sort_bubble(array* a) {
    if (! a) {
        return 1;
    }

    int sz = array_size(a);
    if (sz < 2) {
        return 0;
    }

    int limit;
    int sorted_since;
    for (limit=sz; limit>1; limit--) {
        sorted_since = -1;
        int i;
        for (i=1; i<limit; i++) {
            if (a->a[i] < a->a[i-1]) {
                array_swap(a, i, i-1);
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

    return 0;
}
