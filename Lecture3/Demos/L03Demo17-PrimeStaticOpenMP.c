#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    srand(time(0));
    long N = 100000;

    int x, d, prime;

    long numberOfThreadsToUse[] = {1, 2, 3, 4, 5, 6, 12, 24};
    int iterationCount = sizeof(numberOfThreadsToUse) / sizeof(long);

    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++) {
        long currentNumberOfCores = numberOfThreadsToUse[currentIteration];
        int counter = 0;

        omp_set_num_threads(currentNumberOfCores);
        double t1 = omp_get_wtime();

        #pragma omp parallel for reduction(+:counter) private(prime,d) schedule(static)
        for (int x = 1; x <= N; x++)
        {
            prime = 0;
            for (int d = 2; d <= x / 2; d++)
                if (x % d == 0)
                    prime = 1;
            if (prime == 0)
                counter++;
        }
   
        double t2 = omp_get_wtime();
        printf("\nNumber of primes=%d ,Thread count = %ld, time = %.6f\n", counter, currentNumberOfCores, t2 - t1);
    }

    return 0;
}
