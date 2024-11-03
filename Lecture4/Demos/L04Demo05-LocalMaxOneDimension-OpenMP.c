#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    long arrayLengths[] = {20, 2000000, 20000000};
    // long arrayLengths[] = {20};
    int iterationCount = sizeof(arrayLengths) / sizeof(long);
    int w = 5;

    srand(time(0));

    printf("Iterations:%d  , No of threads %d , Window size %d\n", iterationCount, omp_get_max_threads(), w);
    printf("Size          Sequential(s)   Parallel(s)   Speedup   Efficiency  Sequential Max Count Parallel Max Count\n");
    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++)
    {
        long currentDataLength = arrayLengths[currentIteration];
        int *A, *B, *C;

        A = malloc(currentDataLength * sizeof(int));
        B = malloc(currentDataLength * sizeof(int));
        C = malloc(currentDataLength * sizeof(int));
        for (int i = 0; i < currentDataLength; i++)
        {
            A[i] = rand() % 10;
            B[i] = 0;
            C[i] = 0;
        }

        // Sequential logic
        double sequential_start_time = omp_get_wtime();
        for (int i = w; i < currentDataLength - w; i++)
        {
            int isMaximum = 1;
            for (int j = i - w; j < i; j++)
                if (A[j] >= A[i])
                    isMaximum = 0;

            for (int j = i + 1; j <= i + w; j++)
                if (A[j] >= A[i])
                    isMaximum = 0;

            if (isMaximum == 1)
                B[i] = A[i];
        }

        double sequential_end_time = omp_get_wtime();
        double sequential_elapsed_time = sequential_end_time - sequential_start_time;

        printf("%010ld    %.6f", currentDataLength, sequential_elapsed_time);

        // Parallel logic
        double parallel_start_time = omp_get_wtime();
        int parallel_i;
#pragma omp parallel for
        for (parallel_i = w; parallel_i < currentDataLength - w; parallel_i++)
        {
            int isMaximum = 1;
            for (int j = parallel_i - w; j < parallel_i; j++) // left
            {
                if (A[j] >= A[parallel_i])
                    isMaximum = 0;
            }

            for (int j = parallel_i + 1; j <= parallel_i + w; j++) // right
            {
                if (A[j] >= A[parallel_i])
                    isMaximum = 0;
            }

            if (isMaximum == 1)
            {
                C[parallel_i] = A[parallel_i];
            }
        }

        double parallel_end_time = omp_get_wtime();
        double parallel_elapsed_time = parallel_end_time - parallel_start_time;

        printf("        %.6f", parallel_elapsed_time);
        // End of Parallel logic

        double speedup = sequential_elapsed_time / parallel_elapsed_time;
        double efficiency = speedup / omp_get_max_threads();

        // Counts
        int maxCountSeq = 0;
        int maxCountParallel = 0;
        for (int i = 0; i < currentDataLength; i++)
        {
            if (B[i] > 0)
            {
                maxCountSeq++;
            }
            if (C[i] > 0)
            {
                maxCountParallel++;
            }
        }

        printf("      %.6f", speedup);
        printf("  %.6f   %-5d                %-5d \n", efficiency, maxCountSeq, maxCountParallel);
        printf("\n");

        if (currentDataLength <= 20)
        {
            printf("\n\n\t\tOriginal Array \n\n\t\t");
            for (int i = 0; i < currentDataLength; i++)
            {
                printf("%3d", A[i]);
            }

            printf("\n\n\t\tB \n\n\t\t");
            for (int i = 0; i < currentDataLength; i++)
            {
                if (B[i] == 0)
                    printf("-- ");
                else
                    printf("%3d", B[i]);
            }
            printf("\n\n\t\tC \n\n\t\t");
            for (int i = 0; i < currentDataLength; i++)
            {
                if (C[i] == 0)
                    printf("-- ");
                else
                    printf("%3d", C[i]);
            }

            printf("\n\n");
        }

        for (int i = 0; i < currentDataLength; i++)
            if (B[i] != C[i])
                printf("\n Error in calculation ");

        free(A);
        free(B);
        free(C);
    }

    return 0;
}