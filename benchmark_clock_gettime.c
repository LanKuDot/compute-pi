#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "computepi.h"

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

#define NUM_OF_SAMPLE 25
#define POW2(X) ((X)*(X))

/**
 * @brief Get the mean of the mother with 95% ci from samples.
 */
static double getMean(double samples[NUM_OF_SAMPLE])
{
    double sample_mean, sample_sd;
    int i;

    /* Calculate sample mean */
    sample_mean = 0.0;
    for (i = 0; i < NUM_OF_SAMPLE; ++i)
        sample_mean += samples[i];
    sample_mean /= NUM_OF_SAMPLE;

    /* Calculate sample standard deviation */
    sample_sd = 0.0;
    for (i = 0; i < NUM_OF_SAMPLE; ++i)
        sample_sd += POW2(samples[i] - sample_mean);
    sample_sd /= (NUM_OF_SAMPLE - 1);
    sample_sd = sqrt(sample_sd);

    /* Compute mother mean */
    return sample_mean - (2.06 * sample_sd / sqrt(NUM_OF_SAMPLE));
}

int main(int argc, char const *argv[])
{
    struct timespec start = {0, 0};
    struct timespec end = {0, 0};

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 25;

    // Baseline
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_baseline(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // OpenMP with 2 threads
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_openmp(N, 2);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // OpenMP with 4 threads
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_openmp(N, 4);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf\n", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // AVX SIMD
/*    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_avx(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf,", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);


    // AVX SIMD + Loop unrolling
    clock_gettime(CLOCK_ID, &start);
    for(i = 0; i < loop; i++) {
        compute_pi_avx_unroll(N);
    }
    clock_gettime(CLOCK_ID, &end);
    printf("%lf\n", (double) (end.tv_sec - start.tv_sec) +
           (end.tv_nsec - start.tv_nsec)/ONE_SEC);
*/
    return 0;
}
