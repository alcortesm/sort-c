#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "util.h"
#include "array.h"

int sort_quick(array* a) {
    if (! a) {
        return 1;
    }

    int sz = array_size(a);
    if (sz < 2) {
        return 0;
    }

    return 0;
}
