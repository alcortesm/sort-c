#include <stdlib.h>

#include <util.h>

#include "test.h"
#include "test_util.h"
#include "test_sort.h"

int main(int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);

    int fail;
    test_fn tests[] = {
        &test_util,
        &test_sort,
    };
    int ntests = sizeof(tests) / sizeof(test_fn);

    int i;
    for (i=0; i<ntests; i++) {
        fail =  tests[i](NULL);
        if (fail) {
            return fail;
        }
    }

    return 0;
}
