compile: count_primes_serial.cpp
	g++ count_primes_serial.cpp -o count_primes_serial -fopenmp 

run:
	perf stat ./count_primes_serial
