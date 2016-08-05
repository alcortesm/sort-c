# sort-c [![Build Status](https://travis-ci.org/alcortesm/sort-c.svg?branch=master)](https://travis-ci.org/alcortesm/sort-c) [![codecov](https://codecov.io/gh/alcortesm/sort-c/branch/master/graph/badge.svg)](https://codecov.io/gh/alcortesm/sort-c)

## Benchmarks

Compile the benchmarking suite and run it:

```
; make benchmark
...
;
; ./benchmark/benchmarkall
Benchmarks for "bubble sort":
	benchmark length =   1000,		result =   0.763 milliseconds
	benchmark length =   2000,		result =   2.857 milliseconds
	benchmark length =   3000,		result =   6.590 milliseconds
	benchmark length =   4000,		result =  12.460 milliseconds
	benchmark length =   5000,		result =  21.172 milliseconds
Benchmarks for "merge sort (n space)":
	benchmark length =   1000,		result =   0.067 milliseconds
	benchmark length =   2000,		result =   0.147 milliseconds
	benchmark length =   3000,		result =   0.224 milliseconds
	benchmark length =   4000,		result =   0.302 milliseconds
	benchmark length =   5000,		result =   0.385 milliseconds
```

