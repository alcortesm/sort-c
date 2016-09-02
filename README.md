# sort-c [![Build Status](https://travis-ci.org/alcortesm/sort-c.svg?branch=master)](https://travis-ci.org/alcortesm/sort-c) [![codecov](https://codecov.io/gh/alcortesm/sort-c/branch/master/graph/badge.svg)](https://codecov.io/gh/alcortesm/sort-c)

## Benchmarks

Compile the benchmarking suite and run it:

```
; make benchmark
...
./benchmarkall
Benchmarks for "merge sort (n space)":
        array length =  100000, runs = 100,     mean =   9.900 milliseconds
        array length =  200000, runs = 100,     mean =  20.696 milliseconds
        array length =  300000, runs = 100,     mean =  32.377 milliseconds
        array length =  400000, runs = 100,     mean =  44.070 milliseconds
        array length =  500000, runs = 100,     mean =  56.250 milliseconds
Benchmarks for "quick sort":
        array length =  100000, runs = 100,     mean =   9.643 milliseconds
        array length =  200000, runs = 100,     mean =  20.426 milliseconds
        array length =  300000, runs = 100,     mean =  31.753 milliseconds
        array length =  400000, runs = 100,     mean =  43.367 milliseconds
        array length =  500000, runs = 100,     mean =  55.333 milliseconds
Benchmarks for "heapsort":
        array length =  100000, runs = 100,     mean =  13.955 milliseconds
        array length =  200000, runs = 100,     mean =  30.515 milliseconds
        array length =  300000, runs = 100,     mean =  48.263 milliseconds
        array length =  400000, runs = 100,     mean =  66.457 milliseconds
        array length =  500000, runs = 100,     mean =  85.419 milliseconds
...
```


