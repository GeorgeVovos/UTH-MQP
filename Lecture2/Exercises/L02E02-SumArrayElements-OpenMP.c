#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{

    long arrayLengths[] = {2000000, 20000000, 200000000, 2000000000};
    int iterationCount = sizeof(arrayLengths) / sizeof(long);
    float P = 3.14159;

    srand(time(0));

    printf("Iterantions:%d  , No of threads %d\n", iterationCount, omp_get_max_threads());
    printf("Size          Sequential(s)   Parallel(s)   Speedup   Efficiency\n");
    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++)
    {
        long currentDataLength = arrayLengths[currentIteration];

        int *A = malloc(currentDataLength * sizeof(int));

        for (int i = 0; i < currentDataLength; i++)
        {
            A[i] = rand() % 1000000;
        }

        // Sequential logic

        double sequential_start_time = omp_get_wtime();
        long long sequential_sum = 0;
        for (int seq_i = 0; seq_i < currentDataLength; seq_i++)
        {
            sequential_sum += A[seq_i];
        }

        double sequential_end_time = omp_get_wtime();
        double sequential_elapsed_time = sequential_end_time - sequential_start_time;

        printf("%010d    %.6f", currentDataLength, sequential_elapsed_time);

        // Parallel logic

        double parallel_start_time = omp_get_wtime();
        long long parallel_sum = 0;
        #pragma omp parallel for reduction(+ : parallel_sum)
        for (int parallel_i = 0; parallel_i < currentDataLength; parallel_i++)
        {
            parallel_sum += A[parallel_i];
        }

        double parallel_end_time = omp_get_wtime();
        double parallel_elapsed_time = parallel_end_time - parallel_start_time;

        printf("        %.6f", parallel_elapsed_time);

        // End of Parallel logic

        double speedup = sequential_elapsed_time / parallel_elapsed_time;
        double efficiency = speedup / omp_get_max_threads();
        printf("      %.6f", speedup);
        printf("  %.6f", efficiency);

        if (sequential_sum != parallel_sum)
        {
            printf("The outcomes don't match");
        }

        printf("\n");

        free(A);
    }

    return 0;
}
