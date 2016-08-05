# sort-c [![Build Status](https://travis-ci.org/alcortesm/sort-c.svg?branch=master)](https://travis-ci.org/alcortesm/sort-c) [![codecov](https://codecov.io/gh/alcortesm/sort-c/branch/master/graph/badge.svg)](https://codecov.io/gh/alcortesm/sort-c)

## Benchmarks

Compile the benchmarking suite and run it:

```
; make benchmark
...
;
; ./benchmark/benchmarkall
Benchmarks for "bubble sort":
        benchmark length =      10000,          result =   120.631 milliseconds
        benchmark length =      20000,          result =   591.226 milliseconds
        benchmark length =      30000,          result =  1428.283 milliseconds
        benchmark length =      40000,          result =  2649.561 milliseconds
        benchmark length =      50000,          result =  4196.430 milliseconds
Benchmarks for "merge sort (n space)":
        benchmark length =      10000,          result =     0.837 milliseconds
        benchmark length =      20000,          result =     1.841 milliseconds
        benchmark length =      30000,          result =     2.843 milliseconds
        benchmark length =      40000,          result =     3.836 milliseconds
        benchmark length =      50000,          result =     4.855 milliseconds
```

