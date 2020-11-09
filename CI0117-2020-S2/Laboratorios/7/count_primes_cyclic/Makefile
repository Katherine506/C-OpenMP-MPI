compile: count_primes_cyclic.cpp
	g++ -o count_primes_cyclic count_primes_cyclic.cpp -ggdb3 -Wall -fopenmp -lm

run:
	export OMP_SCHEDULE="dynamic,1"
	perf stat ./count_primes_cyclic 