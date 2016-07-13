#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <util.h>

#include "test.h"

int test_strdup(const char*);

int test_util() {
    test_fn tests[] = {
        test_strdup,
    };
    int ntests = sizeof(tests)/sizeof(test_fn);

    int i;
    int fail;
    for (i=0; i<ntests; i++) {
        fail = tests[i]("test_util");
        if (fail) {
            return fail;
        }
    }

    return 0;
}

int test_strdup(const char* prefix) {
    const char* tests[] = {
        "",
        "a",
        "ab",
        "abcdefghijklmnopq",
    };
    int ntests = sizeof(tests) / sizeof(char*);

    int i;
    const char* input;
    char* obtained;
    for (i=0; i<ntests; i++) {
        input = tests[i];
        obtained = strdup(input);
        if (obtained == input) {
            printf("%s/test_strdup: test %d failed\n", prefix, i);
            printf("\tobtained and expected have the same mem address\n");
            return 1;
        }
        if (strcmp(obtained, input) != 0) {
            printf("%s/test_strdup: test %d failed\n", prefix, i);
            printf("\texpected = \"%s\"\n", input);
            printf("\tobtained = \"%s\"\n", obtained);
            free(obtained);
            return 2;
        }

        free(obtained);
    }

    return 0;
}

