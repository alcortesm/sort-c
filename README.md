# sort-c [![Build Status](https://travis-ci.org/alcortesm/sort-c.svg?branch=master)](https://travis-ci.org/alcortesm/sort-c) [![codecov](https://codecov.io/gh/alcortesm/sort-c/branch/master/graph/badge.svg)](https://codecov.io/gh/alcortesm/sort-c)

## Benchmarks

Compile the benchmarking suite and run it:

```
; make benchmark 
mkdir obj/
cc -c -Wall -Wextra -Wpedantic -Werror -std=c99 -O3 -iquote include/ -o obj/util.o src/util.c
cc -c -Wall -Wextra -Wpedantic -Werror -std=c99 -O3 -iquote include/ -o obj/array.o src/array.c
cc -c -Wall -Wextra -Wpedantic -Werror -std=c99 -O3 -iquote include/ -o obj/bubble.o src/bubble.c
cc -c -Wall -Wextra -Wpedantic -Werror -std=c99 -O3 -iquote include/ -o obj/merge_nspace.o src/merge_nspace.c
mkdir lib/
ar -cvr lib/libsort.a obj/util.o obj/array.o obj/bubble.o obj/merge_nspace.o
a - obj/util.o
a - obj/array.o
a - obj/bubble.o
a - obj/merge_nspace.o
cd benchmark/ ; make benchmark
make[1]: Entering directory '/home/alberto/room/src/cspace/sort-c/benchmark'
cc -Wall -Wextra -Wpedantic -Werror -std=c99 -O3  -I ../include/ -c -o benchmark.o benchmark.c
cc -o benchmarkall benchmark.o -L ../lib/ -l sort
./benchmarkall
Benchmarks for "bubble sort":
        benchmark length =       1000,          result =   0.00 seg
        benchmark length =      10000,          result =   0.12 seg
        benchmark length =     100000,          result =  17.07 seg
Benchmarks for "merge sort (n space)":
        benchmark length =       1000,          result =   0.00 seg
        benchmark length =      10000,          result =   0.00 seg
        benchmark length =     100000,          result =   0.01 seg
make[1]: Leaving directory '/home/alberto/room/src/cspace/sort-c/benchmark'
```

