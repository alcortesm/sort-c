#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include <util.h>
#include <sort.h>

void  benchmark_algo(sort_fn* fn);
float benchmark_func(sort_fn* fn, int len, int nruns);
void  report(int len, int nruns, float result);

int main(int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);

    time_t seed = time(NULL);
    srand(seed);

    struct named_algo {
        const char* name;
        sort_fn*    fn;
    };

    struct named_algo algos[] = {
        //{"bubble sort",          &sort_bubble},
        {"mergesort (n space)", &sort_merge_nspace},
        {"quicksort",           &sort_quick},
        {"heapsort",            &sort_heap},
    };
    int nalgos = sizeof(algos) / sizeof(struct named_algo);

    int i;
    for (i = 0; i < nalgos; i++) {
        printf("Benchmarks for \"%s\":\n", algos[i].name);
        benchmark_algo(algos[i].fn);
    }

    exit(0);
}

// benchmark a sorting function using several array sizes and prints the
// results.
void benchmark_algo(sort_fn* fn) {
    int nruns = 100;
    int lengths[] = {
        1 * 100000,
        2 * 100000,
        3 * 100000,
        4 * 100000,
        5 * 100000,
    };
    int nlengths = sizeof(lengths) / sizeof(int);

    int i;
    float result;
    for (i = 0; i < nlengths; i++) {
        result = benchmark_func(fn, lengths[i], nruns);
        report(lengths[i], nruns, result);
    }
}

// runs several benchmarks for a given array length and a given sorting
// function and return the mean value of the time it took to sort arrays
// of such length.
float benchmark_func(sort_fn* fn, int len, int nruns) {
    int i;
    int err;
    array* a;
    clock_t start, end;
    double elapsed;
    double total = 0;
    for (i=0; i<nruns; i++) {
        a = array_random(len);

        start = clock();
        err = fn(a);
        end = clock();
        elapsed = (double)(end - start) / CLOCKS_PER_SEC;
        total += elapsed;

        if (err) {
            fprintf(stderr, "sort failed");
            return -1.0;
        }
        array_free(a);
    }

    return total / nruns;
}

void report(int len, int nruns, float result) {
    float ms = result * 1000;
    printf("\tarray length = % 6d,\truns = %d,\tmean = % 7.3f milliseconds\n",
           len, nruns, ms);

    return;
}
