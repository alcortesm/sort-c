#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <util.h>

#include "test.h"

test_fn test_strjoin;
test_fn test_strdup;
test_fn test_to_str;

int test_util(const char* prefix) {
    UNUSED(prefix);

    test_fn* tests[] = {
        &test_strdup,
        &test_strjoin,
        &test_to_str,
    };
    int ntests = sizeof(tests)/sizeof(test_fn*);

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
            printf("%s -> test_strdup: test %d failed\n", prefix, i);
            printf("\tobtained and expected have the same mem address\n");
            return 2;
        }
        if (strcmp(obtained, input) != 0) {
            printf("%s -> test_strdup: test %d failed\n", prefix, i);
            printf("\texpected = \"%s\"\n", input);
            printf("\tobtained = \"%s\"\n", obtained);
            free(obtained);
            return 3;
        }

        free(obtained);
    }

    return 0;
}

int test_strjoin(const char* prefix) {
    char* obtained;
    char* expected;
    int test = 0;

    // test 0
    obtained = strjoin(NULL, NULL);
    if (obtained) {
        printf("%s -> test_strjoin: test %d failed\n", prefix, test);
        printf("\tobtained should be NULL, but was \"%s\"\n", obtained);
        free(obtained);
        return 1;
    }

    // test 1
    test++;
    obtained = strjoin("", NULL);
    if (obtained) {
        printf("%s -> test_strjoin: test %d failed\n", prefix, test);
        printf("\tobtained should be NULL, but was \"%s\"\n", obtained);
        free(obtained);
        return 1;
    }

    // test 2
    test++;
    expected = "";
    obtained = strjoin("", "");
    if (strcmp(obtained, expected) != 0) {
        printf("%s -> test_strjoin: test %d failed\n", prefix, test);
        printf("\texpected = \"%s\"\n", expected);
        printf("\tobtained = \"%s\"\n", obtained);
        free(obtained);
        return 1;
    }
    free(obtained);

    // test 3
    test++;
    expected = "a";
    obtained = strjoin("", "a");
    if (strcmp(obtained, expected) != 0) {
        printf("%s -> test_strjoin: test %d failed\n", prefix, test);
        printf("\texpected = \"%s\"\n", expected);
        printf("\tobtained = \"%s\"\n", obtained);
        free(obtained);
        return 1;
    }
    free(obtained);

    // test 4
    test++;
    expected = "a";
    obtained = strjoin("a", "");
    if (strcmp(obtained, expected) != 0) {
        printf("%s -> test_strjoin: test %d failed\n", prefix, test);
        printf("\texpected = \"%s\"\n", expected);
        printf("\tobtained = \"%s\"\n", obtained);
        free(obtained);
        return 1;
    }
    free(obtained);

    // test 5
    test++;
    expected = "ab";
    obtained = strjoin("a", "b");
    if (strcmp(obtained, expected) != 0) {
        printf("%s -> test_strjoin: test %d failed\n", prefix, test);
        printf("\texpected = \"%s\"\n", expected);
        printf("\tobtained = \"%s\"\n", obtained);
        free(obtained);
        return 1;
    }
    free(obtained);

    // test 6
    test++;
    expected = "a0042.3";
    obtained = strjoin("a", "%06.1f", 42.3241);
    if (strcmp(obtained, expected) != 0) {
        printf("%s -> test_strjoin: test %d failed\n", prefix, test);
        printf("\texpected = \"%s\"\n", expected);
        printf("\tobtained = \"%s\"\n", obtained);
        free(obtained);
        return 1;
    }
    free(obtained);

    // test 7
    test++;
    expected = "a 0042.3 foo";
    obtained = strjoin("a", " %06.1f %s", 42.3241, "foo");
    if (strcmp(obtained, expected) != 0) {
        printf("%s -> test_strjoin: test %d failed\n", prefix, test);
        printf("\texpected = \"%s\"\n", expected);
        printf("\tobtained = \"%s\"\n", obtained);
        free(obtained);
        return 1;
    }
    free(obtained);

    return 0;
}

typedef struct {
    int num_elems;
    int* array;
    char* expected;
} to_str_test;

int test_to_str(const char* prefix) {
    char* where = strjoin(prefix, " -> test_to_str");
    if (!where) {
        return 1;
    }

    to_str_test tests[] = {
        {0, NULL, "{}"},
        {1, (int[]){0}, "{0}"},
        {2, (int[]){0, 1}, "{0, 1}"},
        {3, (int[]){0, 1, 2}, "{0, 1, 2}"},
        {4, (int[]){0, -1, 2, -1234}, "{0, -1, 2, -1234}"},
    };
    int ntests = sizeof(tests) / sizeof(to_str_test);

    int i;
    int* array;
    int num_elems;
    char* expected;
    char* obtained;
    for (i=0; i<ntests; i++) {
        num_elems = tests[i].num_elems;
        array = tests[i].array;
        expected = tests[i].expected;
        obtained = to_str(array, num_elems);
        if (strcmp(obtained, expected) != 0) {
            printf("%s: test %d failed\n", where, i);
            printf("\texpected = \"%s\"\n", expected);
            printf("\tobtained = \"%s\"\n", obtained);
            free(obtained);
            free(where);
            return 2;
        }

        free(obtained);
    }

    free(where);
    return 0;
}

