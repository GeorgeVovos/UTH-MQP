#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main() {
    srand(time(0));
    long numberOfThreadsToUse[] = {1, 2, 3, 4, 5, 6, 12, 24};
    int iterationCount = sizeof(numberOfThreadsToUse) / sizeof(long);
    long totalPoints = 10000000;

    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++) {
        long currentNumberOfCores = numberOfThreadsToUse[currentIteration];
        long points_in_circle = 0;

        omp_set_num_threads(currentNumberOfCores);
        double t1 = omp_get_wtime();

        #pragma omp parallel reduction(+:points_in_circle)
        {
            #pragma omp for
            for (long i = 0; i < totalPoints; i++) {
                double x = (double)rand() / RAND_MAX;
                double y = (double)rand() / RAND_MAX;
                if (x * x + y * y <= 1.0) {
                    points_in_circle++;
                }
            }
        }

        double mypi = 4.0 * (double)points_in_circle / (double)totalPoints;

        double t2 = omp_get_wtime();
        printf("\nPi = %.8f, Thread count = %ld, Time = %.8f\n", mypi, currentNumberOfCores, t2 - t1);
    }

    return 0;
}
