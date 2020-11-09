compile: count_primes_parallel.cpp
	g++ -o count_primes_parallel count_primes_parallel.cpp -ggdb3 -Wall -fopenmp -lm

run:
	perf stat ./count_primes_parallel