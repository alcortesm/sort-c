#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <util.h>

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

int main(int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);

    return util_test();
}

typedef struct {
    char* input;
    char* expected;
} test;

int util_test() {
    test tests[] = {
        {"", ""},
        {"a", "a"},
        {"ab", "ab"},
        {"abcdefghijklmnopq", "abcdefghijklmnopq"},
    };
    int ntests = sizeof(tests) / sizeof(test);

    int i;
    test t;
    char* obtained;
    for (i=0; i<ntests; i++) {
        t = tests[i];
        obtained = strdup(t.input);
        if (obtained == t.input) {
            printf("util_test: test %d failed\n", i);
            printf("\tobtained and expected have the same mem address\n");
            return 1;
        }
        if (strcmp(obtained, t.expected) != 0) {
            printf("util_test: test %d failed\n", i);
            printf("\texpected = \"%s\"\n", t.expected);
            printf("\tobtained = \"%s\"\n", obtained);
            free(obtained);
            return 2;
        }

        free(obtained);
    }

    return 0;
}
