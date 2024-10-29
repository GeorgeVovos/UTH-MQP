#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    srand(time(0));
    long N = 100000;
    int counter = 0;

    double ta = omp_get_wtime();

    for (int x = 1; x <= N; x++)
    {
        int prime = 0;
        for (int d = 2; d <= x / 2; d++)
            if (x % d == 0)
                prime = 1;
        if (prime == 0)
            counter++;
    }
    double tt = omp_get_wtime();
    printf("\nNumber of primes=%d , time = %.6f\n", counter,tt - ta);
    return 0;
}
