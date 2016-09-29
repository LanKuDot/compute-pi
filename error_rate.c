/* Run all cases and calculate the error rate
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "computepi.h"

static double error_rate(double sample, double groundTruth)
{
    return ((sample > groundTruth) ? (sample - groundTruth) :
        (groundTruth - sample)) / groundTruth;
}

int main(int argc, char *argv[])
{
    int N = atoi(argv[1]);

    printf("%.15lf,", error_rate(compute_pi_baseline(N), M_PI));
    printf("%.15lf,", error_rate(compute_pi_openmp(N, 2), M_PI));
    printf("%.15lf\n", error_rate(compute_pi_openmp(N, 4), M_PI));
//  printf("%.15lf,", error_rate(compute_pi_baseline(N), M_PI));
//  printf("%.15lf\n", error_rate(compute_pi_baseline(N), M_PI));
}
