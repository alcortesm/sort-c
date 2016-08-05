# sort-c [![Build Status](https://travis-ci.org/alcortesm/sort-c.svg?branch=master)](https://travis-ci.org/alcortesm/sort-c) [![codecov](https://codecov.io/gh/alcortesm/sort-c/branch/master/graph/badge.svg)](https://codecov.io/gh/alcortesm/sort-c)

## Benchmarks

Compile the benchmarking suite and run it:

```
; make benchmark
...
;
; ./benchmark/benchmarkall
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

