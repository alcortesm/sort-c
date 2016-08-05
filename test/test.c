#include <stdlib.h>

#include <util.h>

#include "test.h"

int main(int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);

    struct named_test {
        test_fn*    fn;
        const char* name;
    };

    struct named_test tests[] = {
        {&test_util,  "test_util"},
        {&test_array, "test_array"},
        {&test_sort,  "test_sort"},
    };
    int ntests = sizeof(tests) / sizeof(struct named_test);

    int i;
    int fail;
    for (i=0; i<ntests; i++) {
        fail =  tests[i].fn(tests[i].name);
        if (fail) {
            return fail;
        }
    }

    return 0;
}
