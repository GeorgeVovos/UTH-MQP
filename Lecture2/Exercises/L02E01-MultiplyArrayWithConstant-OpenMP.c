#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{

    long arrayLengths[] = {2000000, 20000000, 200000000, 400000000, 800000000, 1600000000};
    int iterationCount = sizeof(arrayLengths) / sizeof(long);
    float P = 3.14159;

    srand(time(0));

    printf("Iterantions:%d  , No of threads %d\n", iterationCount, omp_get_max_threads());
    printf("Size          Sequential(s)   Parallel(s)   Speedup   Efficiency\n");
    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++)
    {
        long currentDataLength = arrayLengths[currentIteration];

        int *A = malloc(currentDataLength * sizeof(int));
        double *B = malloc(currentDataLength * sizeof(double));

        for (int i = 0; i < currentDataLength; i++)
        {
            A[i] = rand() % 1000;
        }

        // Sequential logic

        double sequential_start_time = omp_get_wtime();
        for (int seq_i = 0; seq_i < currentDataLength; seq_i++)
        {
            B[seq_i] = P * A[seq_i];
        }

        double sequential_end_time = omp_get_wtime();
        double sequential_elapsed_time = sequential_end_time - sequential_start_time;

        printf("%010ld    %.6f", currentDataLength, sequential_elapsed_time);

        // Parallel logic

        double parallel_start_time = omp_get_wtime();
        int parallel_i;
        #pragma omp parallel for private(parallel_i) shared(A, B, P, currentDataLength)
        for (parallel_i = 0; parallel_i < currentDataLength; parallel_i++)
        {
            B[parallel_i] = P * A[parallel_i];
        }

        double parallel_end_time = omp_get_wtime();
        double parallel_elapsed_time = parallel_end_time - parallel_start_time;

        printf("        %.6f", parallel_elapsed_time);

        // End of Parallel logic

        double speedup = sequential_elapsed_time / parallel_elapsed_time;
        double efficiency = speedup / omp_get_max_threads();
        printf("      %.6f", speedup);
        printf("  %.6f", efficiency);
        printf("\n");

        free(A);
        free(B);
    }

    return 0;
}
