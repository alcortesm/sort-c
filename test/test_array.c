#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <util.h>
#include <array.h>

#include "test.h"

test_fn test_array_new;
test_fn test_array_to_str;
test_fn test_array_equals;
test_fn test_array_clone;

int test_array(const char* prefix) {
    struct named_test {
        test_fn*    fn;
        const char* name;
    };

    struct named_test tests[] = {
        {&test_array_new, "test_array_new"},
        {&test_array_to_str, "test_array_to_str"},
        {&test_array_equals, "test_array_equals"},
        {&test_array_clone, "test_array_clone"},
    };
    int ntests = sizeof(tests) / sizeof(struct named_test);

    int i;
    int fail;
    char* text;
    for (i=0; i<ntests; i++) {
        text = strjoin(prefix, " -> %s", tests[i].name);
        if (! text) {
            perror("strjoin");
            exit(1);
        }

        fail =  tests[i].fn(text);
        if (fail) {
            return fail;
        }

        free(text);
    }

    return 0;
    return test_array_new(prefix);
}

char* comment(const char* str, int num) {
    char* format = "%s, test number %d:";
    int n = snprintf(NULL, 0, format, str, num);

    char* s = (char*) malloc((1+n) * sizeof(char));
    if (! s) {
        return NULL;
    }

    n = sprintf(s, format, str, num);
    if (n < 0) {
        free(s);
        return NULL;
    }

    return s;
}

void report_error_did_not_fail(const char* prefix, int test_num,
                               int* data, int data_len,
                               int expected_error, array* obtained) {

    char* s = comment(prefix, test_num);
    if (! s) {
        perror("comment");
        exit(1);
    }
    printf("%s FAIL\n", s);
    free(s);

    printf("\texpected an error, but none was returned\n");

    s = to_str(data, data_len);
    if (! s) {
        perror("to_str");
        exit(1);
    }
    printf("\t\tinput  a: %s\n", s);
    free(s);

    printf("\t\t       n: %d\n", data_len);
    printf("\t\t   error: %d\n", expected_error);

    s = array_to_str(obtained);
    printf("\t\tobtained: %s\n", s);
    free(s);
}

void report_error_unexpected(const char* prefix, int test_num,
                             int* data, int data_len,
                             int expected_error) {

    char* s = comment(prefix, test_num);
    if (! s) {
        perror("comment");
        exit(1);
    }
    printf("%s FAIL\n", s);
    free(s);

    printf("\tunexpected error\n");
    s = to_str(data, data_len);
    if (! s) {
        perror("to_str");
        exit(1);
    }
    printf("\t\tinput  a: %s\n", s);
    free(s);

    printf("\t\t       n: %d\n", data_len);
    printf("\t\t   error: %d\n", expected_error);
    printf("\t\tobtained: NULL\n");
}

int different_size(array* a, int sz) {
    return (sz != array_size(a));
}

void report_error_different_size(const char* prefix, int test_num,
                                 int* data, int data_len,
                                 array* obtained) {

    char* s = comment(prefix, test_num);
    if (! s) {
        perror("comment");
        exit(1);
    }
    printf("%s FAIL\n", s);
    free(s);

    printf("\tdifferent size\n");
    s = to_str(data, data_len);
    if (! s) {
        perror("to_str");
        exit(1);
    }
    printf("\t\tinput  a: %s\n", s);
    free(s);

    printf("\t\t       n: %d\n", data_len);

    s = array_to_str(obtained);
    printf("\tobtained: %s\n", s);
    free(s);
}

int different_content(array* a, int* data, int data_len) {
    int i;
    for (i=0; i<data_len; i++) {
        if (a->a[i] != data[i]) {
            return 1;
        }
    }

    return 0;
}

void report_error_different_content(const char* prefix, int test_num,
                                    int* data, int data_len,
                                    array* obtained) {

    char* s = comment(prefix, test_num);
    if (! s) {
        perror("comment");
        exit(1);
    }
    printf("%s FAIL\n", s);
    free(s);

    printf("\tdifferent content\n");
    s = to_str(data, data_len);
    if (! s) {
        perror("to_str");
        exit(1);
    }
    printf("\t\tinput  a: %s\n", s);
    free(s);

    printf("\t\t       n: %d\n", data_len);

    s = array_to_str(obtained);
    printf("\tobtained: %s\n", s);
    free(s);
}

int test_array_new(const char* prefix) {
    typedef struct {
        int* a;
        int  n;
        int  error;
    } fix;

    fix tests[] = {
        {NULL, 1, 1},
        {NULL, -1, 1},
        {NULL, 0, 0},
        {(int[]){0}, 1, 0},
        {(int[]){0}, -1, 1},
        {(int[]){0, 1}, 2, 0},
        {(int[]){0, 1}, -2, 1},
        {(int[]){0, 1, 2}, 3, 0},
        {(int[]){-3, 12, -1234}, 3, 0},
        {(int[]){-3, 12, -1234, 5, 12, 52, 32, 1900}, 8, 0},
    };
    int ntests = sizeof(tests) / sizeof(fix);

    int i;
    array* obtained;
    for (i=0; i<ntests; i++) {
        obtained = array_new(tests[i].a, tests[i].n);

        if (tests[i].error && obtained) {
            report_error_did_not_fail(prefix, i, tests[i].a,
                                      tests[i].n, tests[i].error,
                                      obtained);
            return 1;
        }

        if (tests[i].error && ! obtained) {
            continue;
        }

        if (! obtained) {
            report_error_unexpected(prefix, i, tests[i].a,
                                          tests[i].n, tests[i].error);
            return 2;
        }

        if (different_size(obtained, tests[i].n)) {
            report_error_different_size(prefix, i, tests[i].a,
                                        tests[i].n, obtained);
            return 3;
        }

        if (different_content(obtained, tests[i].a, tests[i].n)) {
            report_error_different_content(prefix, i, tests[i].a,
                                            tests[i].n, obtained);
            return 3;
        }

        array_free(obtained);
    }

    return 0;
}

int test_array_to_str(const char* prefix) {
    typedef struct {
        array a;
        char* s;
    } fix;

    fix tests[] = {
        {{NULL, 0}, "{}"},
        {{(int[]){0}, 1}, "{0}"},
        {{(int[]){0, 1}, 2}, "{0, 1}"},
        {{(int[]){-1, 0, 13, -50}, 4}, "{-1, 0, 13, -50}"},
    };
    int ntests = sizeof(tests) / sizeof(fix);

    int i;
    char* obtained;
    for (i=0; i<ntests; i++) {
        obtained = array_to_str(&(tests[i].a));

        if (strcmp(tests[i].s, obtained) != 0) {
            char* s = comment(prefix, i);
            if (! s) {
                perror("comment");
                exit(1);
            }
            printf("%s FAIL\n", s);
            free(s);

            printf("\tdifferent strings:\n");
            printf("\t\texpected: %s\n", tests[i].s);
            printf("\t\tobtained: %s\n", obtained);
            return 1;
        }

        free(obtained);
    }

    return 0;
}

int test_array_equals(const char* prefix) {
    typedef struct {
        array a;
        array b;
        int   equals;
    } fix;

    fix tests[] = {
        {{NULL, 0}, {NULL, 0}, 1},
        {{NULL, 0}, {(int[]){0}, 1}, 0},
        {{(int[]){0}, 1}, {NULL, 0}, 0},
        {{(int[]){0}, 1}, {(int[]){0}, 1}, 1},
        {{(int[]){1}, 1}, {(int[]){0}, 1}, 0},
        {{(int[]){0}, 1}, {(int[]){1}, 1}, 0},
        {{(int[]){1}, 1}, {(int[]){1}, 1}, 1},
        {{(int[]){0, 1}, 2}, {(int[]){0, 1}, 2}, 1},
        {{(int[]){0, 1}, 2}, {(int[]){0}, 1}, 0},
        {{(int[]){0, 1}, 2}, {NULL, 0}, 0},
        {{(int[]){0, 1}, 2}, {(int[]){1, 1}, 2}, 0},
        {{(int[]){0, 1}, 2}, {(int[]){0, -1}, 2}, 0},
        {
            {(int[]){0, 1, 2, 3, 4, 5}, 6},
            {(int[]){0, 1, 2, 3, 4, 5}, 6}, 1
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 6},
            {(int[]){0, 1, 2, 2, 4, 5}, 6}, 0
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 6},
            {(int[]){0, 1, 2, 3, 4, 1}, 6}, 0
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 6},
            {(int[]){1, 1, 2, 3, 4, 5}, 6}, 0
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 6},
            {(int[]){0, 1, 1, 3, 4, 5}, 6}, 0
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 6},
            {(int[]){0, 1, 2, 3, 1, 5}, 6}, 0
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 6},
            {(int[]){0, 1, 2, 3, 4, 5}, 5}, 0
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 5},
            {(int[]){0, 1, 2, 3, 4, 5}, 5}, 1
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 5},
            {(int[]){0, 1, 2, 3, 4, 5}, 6}, 0
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 2},
            {(int[]){0, 1, 2, 3, 4, 5}, 1}, 0
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 0},
            {NULL, 0}, 1
        }, {
            {(int[]){0, 1, 2, 3, 4, 5}, 1},
            {(int[]){0, 1, 2, 3}, 1}, 1
        }, {
            {(int[]){0, 1}, 2},
            {(int[]){0, 1, 2, 3, 4, 5}, 2}, 1
        }, {
            {(int[]){0, 1, 2, 3, 4}, 3},
            {(int[]){0, 1, 2, 3, 4, 5}, 3}, 1
        },
    };
    int ntests = sizeof(tests) / sizeof(fix);

    int i;
    int obtained;
    for (i=0; i<ntests; i++) {
        obtained = array_equals(&(tests[i].a), &(tests[i].b));

        if (obtained != tests[i].equals) {
            char* s = comment(prefix, i);
            if (! s) {
                perror("comment");
                exit(1);
            }
            printf("%s FAIL\n", s);
            free(s);

            printf("\tdifferent equals:\n");

            s = array_to_str(&(tests[i].a));
            printf("\t\t       a: %s\n", s);
            free(s);

            s = array_to_str(&(tests[i].b));
            printf("\t\t       b: %s\n", s);
            free(s);

            printf("\t\texpected: %d\n", tests[i].equals);
            printf("\t\tobtained: %d\n", obtained);
            return 1;
        }
    }

    return 0;
}

int test_array_clone(const char* prefix) {
    array tests[] = {
        {NULL, 0},
        {(int[]){0}, 1},
        {(int[]){0, 1}, 2},
        {(int[]){0, 1, 2}, 3},
        {(int[]){0, 1, 2, 3, 4}, 3},
        {(int[]){0, 1, 2, 3, 4}, 4},
        {(int[]){0, 1, 2, 3, 4}, 5},
        {(int[]){0, -1, 2, -3, 4}, 5},
    };
    int ntests = sizeof(tests) / sizeof(array);

    int i;
    array* obtained;
    for (i=0; i<ntests; i++) {
        obtained = array_clone(tests+i);

        if (! array_equals(obtained, tests+i)) {
            char* s = comment(prefix, i);
            if (! s) {
                perror("comment");
                exit(1);
            }
            printf("%s FAIL\n", s);
            free(s);

            printf("\tclone is not equal:\n");

            s = array_to_str(tests+i);
            printf("\t\t   input: %s\n", s);
            free(s);

            s = array_to_str(obtained);
            printf("\t\t   clone: %s\n", s);
            free(s);

            return 1;
        }
    }

    return 0;
}
