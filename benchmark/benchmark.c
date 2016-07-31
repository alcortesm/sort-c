#include <stdlib.h>
#include <stdio.h>

#include <util.h>
#include <array.h>
#include <sort.h>

void  benchmark_algo(sort_fn* fn);
float benchmark_func(sort_fn* fn, int len);
void  report(int len, float result);

int main(int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);

    struct named_algo {
        const char* name;
        sort_fn*    fn;
    };

    struct named_algo algos[] = {
        {"bubble sort",          &sort_bubble},
        {"merge sort (n space)", &sort_merge_nspace},
    };
    int nalgos = sizeof(algos) / sizeof(struct named_algo);

    int i;
    for (i = 0; i < nalgos; i++) {
        printf("Benchmark for \"%s\":\n", algos[i].name);
        benchmark_algo(algos[i].fn);
    }

    exit(0);
}

// benchmark a sorting function using several array sizes and prints the
// results.
void benchmark_algo(sort_fn* fn) {
    int lengths[] = {
        1 * 1000,
        10 * 1000,
        100 * 1000
    };
    int nlengths = sizeof(lengths) / sizeof(int);

    int i;
    float result;
    for (i = 0; i < nlengths; i++) {
        result = benchmark_func(fn, lengths[i]);
        report(lengths[i], result);
    }
}

// runs several benchmarks for a given array length and a given sorting
// function and return the mean value to sort them.
float benchmark_func(sort_fn* fn, int len) {
    UNUSED(fn);
    UNUSED(len);

    return 0.0;
}

void report(int len, float result) {
    printf("\tbenchmark length = % 10d,\t\tresult = % 6.2f seg\n",
           len, result);

    return;
}
