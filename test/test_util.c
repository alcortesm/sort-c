#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <util.h>

#include "test_util.h"

int test_util() {
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
            printf("util_test: test %d failed\n", i);
            printf("\tobtained and expected have the same mem address\n");
            return 1;
        }
        if (strcmp(obtained, input) != 0) {
            printf("util_test: test %d failed\n", i);
            printf("\texpected = \"%s\"\n", input);
            printf("\tobtained = \"%s\"\n", obtained);
            free(obtained);
            return 2;
        }

        free(obtained);
    }

    return 0;
}

