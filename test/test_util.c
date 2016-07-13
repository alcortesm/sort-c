#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <util.h>

#include "test.h"

int test_strdup(const char*);
int test_to_str(const char*);

int test_util() {
    test_fn tests[] = {
        test_strdup,
        test_to_str,
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

char* join(const char* a, const char* b) {
    size_t alen = strlen(a);
    size_t blen = strlen(b);
    char* new = (char*) malloc(1 + alen + blen);
    if (!new) {
        return NULL;
    }

    strcpy(new, a);
    strcpy(new+alen, b);

    return new;
}

int test_strdup(const char* prefix) {
    char* where = join(prefix, " -> test_strdup");
    if (!where) {
        return 1;
    }

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
            printf("%s: test %d failed\n", where, i);
            printf("\tobtained and expected have the same mem address\n");
            free(where);
            return 2;
        }
        if (strcmp(obtained, input) != 0) {
            printf("%s: test %d failed\n", where, i);
            printf("\texpected = \"%s\"\n", input);
            printf("\tobtained = \"%s\"\n", obtained);
            free(obtained);
            free(where);
            return 3;
        }

        free(obtained);
    }

    free(where);
    return 0;
}

typedef struct {
    int num_elems;
    int* array;
    char* expected;
} to_str_test;

int test_to_str(const char* prefix) {
    char* where = join(prefix, " -> test_to_str");
    if (!where) {
        return 1;
    }

    to_str_test tests[] = {
        {0, NULL, "{}"},
        {1, (int*){0}, "{0}"},
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

