#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    srand(time(0));
    long N = 200000;

    int x, d, prime;

    long numberOfThreadsToUse[] = {1, 2, 3, 4, 5, 6, 12, 24};
    int iterationCount = sizeof(numberOfThreadsToUse) / sizeof(long);

    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++) {
        long currentNumberOfCores = numberOfThreadsToUse[currentIteration];
        int counter = 0;

        omp_set_num_threads(currentNumberOfCores);
        double t1 = omp_get_wtime();

        // Since the amount of work for each thread depends on our current iteration, and later iterations will be much more expensive than 
        // earlier ones, we want to use "guided" schedule instead of static or even dynamic
        #pragma omp parallel for reduction(+:counter) private(prime,d) schedule(guided,)
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
        printf("\nGuided Number of primes=%d ,Thread count = %ld, time = %.6f", counter, currentNumberOfCores, t2 - t1);
    }

    printf("\n");
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
        printf("\nStatic Number of primes=%d ,Thread count = %ld, time = %.6f", counter, currentNumberOfCores, t2 - t1);
    }

    printf("\n");
    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++) {
        long currentNumberOfCores = numberOfThreadsToUse[currentIteration];
        int counter = 0;

        omp_set_num_threads(currentNumberOfCores);
        double t1 = omp_get_wtime();
        #pragma omp parallel for reduction(+:counter) private(prime,d) schedule(dynamic)
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
        printf("\nDynamic Number of primes=%d ,Thread count = %ld, time = %.6f", counter, currentNumberOfCores, t2 - t1);
    }
    
    printf("\n");
    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++) {
        long currentNumberOfCores = numberOfThreadsToUse[currentIteration];
        int counter = 0;

        omp_set_num_threads(currentNumberOfCores);
        double t1 = omp_get_wtime();
        #pragma omp parallel for reduction(+:counter) private(prime,d) schedule(dynamic,100)
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
        printf("\nDynamic(100) Number of primes=%d ,Thread count = %ld, time = %.6f", counter, currentNumberOfCores, t2 - t1);
    }

    return 0;
}
