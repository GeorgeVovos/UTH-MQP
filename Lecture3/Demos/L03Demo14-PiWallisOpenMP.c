#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    long numberOfThreadsToUse[] = {1, 2, 3, 4, 5, 6, 12, 24};
    int iterationCount = sizeof(numberOfThreadsToUse) / sizeof(long);
    int N = 10000000; 

    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++) {
        long currentNumberOfCores = numberOfThreadsToUse[currentIteration];
        double mypi = 1.0;

        omp_set_num_threads(currentNumberOfCores);
        double t1 = omp_get_wtime();

        #pragma omp parallel for reduction(*:mypi)
        for (int i = 1; i <= N; i++) {
              mypi *= (4.0 * i * i) / (4.0 * i * i - 1);
        }
        
        mypi *= 2;

        double t2 = omp_get_wtime();
        printf("\nPi = %.8f, Thread count = %ld, Time = %.8f\n", mypi, currentNumberOfCores, t2 - t1);
    }

    return 0;
}
