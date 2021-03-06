CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall -fopenmp #-mavx
EXECUTABLE = \
	time_test_baseline time_test_openmp_2 time_test_openmp_4 \
	benchmark_clock_gettime
#	time_test_avx time_test_avxunroll \

default: computepi.o
	$(CC) $(CFLAGS) computepi.o time_test.c -DBASELINE -o time_test_baseline -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2 -o time_test_openmp_2 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4 -o time_test_openmp_4 -lm
#	$(CC) $(CFLAGS) computepi.o time_test.c -DAVX -o time_test_avx -lm
#	$(CC) $(CFLAGS) computepi.o time_test.c -DAVXUNROLL -o time_test_avxunroll -lm
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime.c -o benchmark_clock_gettime -lm
	$(CC) $(CFLAGS) computepi.o error_rate.c -o error_rate -lm

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

check: default
	time ./time_test_baseline
	time ./time_test_openmp_2
	time ./time_test_openmp_4
#	time ./time_test_avx
#	time ./time_test_avxunroll

gencsv: default
	for i in `seq 100 10000 1000000`; do \
		printf "%d," $$i;\
		./benchmark_clock_gettime $$i; \
	done > result_clock_gettime.csv	
	for i in `seq 100 10000 1000000`; do \
		printf "%d," $$i;\
		./error_rate $$i; \
	done > error_rate.csv

plot:
	gnuplot -e "csvFile='result_clock_gettime.csv'" plottime.gp -presist
	gnuplot -e "csvFile='error_rate.csv'" plotError_log.gp -presist

clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv
