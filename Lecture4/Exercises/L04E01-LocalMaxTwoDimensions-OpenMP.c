#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    int rowCounts[] = {15, 500, 2000, 5000, 9000};
    int colCounts[] = {15, 500, 2000, 5000, 9000};
    int iterationCount = sizeof(rowCounts) / sizeof(int);
    int w = 4;

    srand(time(0));

    printf("Iterations: %d, No of threads: %d, Window size: %d\n", iterationCount, omp_get_max_threads(), w);
    printf("Rows x Cols     Sequential(s)   Parallel(s)   Speedup   Efficiency Sequential Max Count Parallel Max Count\n");

    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++)
    {
        int rows = rowCounts[currentIteration];
        int cols = colCounts[currentIteration];

        int **A = (int **)malloc(rows * sizeof(int *)); //Our initial array
        int **B = (int **)malloc(rows * sizeof(int *)); //The result of the Sequential algorithm
        int **C = (int **)malloc(rows * sizeof(int *)); //The result of the Parallel algorithm

        for (int i = 0; i < rows; i++)
        {
            A[i] = (int *)malloc(cols * sizeof(int));
            B[i] = (int *)malloc(cols * sizeof(int));
            C[i] = (int *)malloc(cols * sizeof(int));
        }

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                A[i][j] = rand() % 10;
                B[i][j] = 0;
                C[i][j] = 0;
            }
        }

        // Sequential logic
        double sequential_start_time = omp_get_wtime();
        for (int i = w; i < rows - w; i++)
        {
            for (int j = w; j < cols - w; j++)
            {
                int isMaximum = 1;
                for (int di = -w; di <= w && isMaximum; di++)
                {
                    for (int dj = -w; dj <= w && isMaximum; dj++)
                    {
                        if (di == 0 && dj == 0)
                            continue;
                        if (A[i + di][j + dj] >= A[i][j])
                        {
                            isMaximum = 0;
                        }
                    }
                }

                if (isMaximum)
                {
                    B[i][j] = A[i][j];
                }
            }
        }
        double sequential_end_time = omp_get_wtime();
        double sequential_elapsed_time = sequential_end_time - sequential_start_time;

        printf("%4dx%4d       %.6f", rows, cols, sequential_elapsed_time);

        // Parallel logic
        double parallel_start_time = omp_get_wtime();
        #pragma omp parallel for collapse(2)
        for (int i = w; i < rows - w; i++)
        {
            for (int j = w; j < cols - w; j++)
            {
                int isMaximum = 1;

                for (int di = -w; di <= w && isMaximum; di++)
                {
                    for (int dj = -w; dj <= w && isMaximum; dj++)
                    {
                        if (di == 0 && dj == 0)
                            continue;
                        if (A[i + di][j + dj] >= A[i][j])
                        {
                            isMaximum = 0;
                        }
                    }
                }

                if (isMaximum)
                {
                    C[i][j] = A[i][j];
                }
            }
        }
        double parallel_end_time = omp_get_wtime();
        double parallel_elapsed_time = parallel_end_time - parallel_start_time;

        printf("        %.6f", parallel_elapsed_time);

        // Calculate speedup and efficiency
        double speedup = sequential_elapsed_time / parallel_elapsed_time;
        double efficiency = speedup / omp_get_max_threads();

        // Counts
        int maxCountSeq = 0;
        int maxCountParallel = 0;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (B[i][j] > 0)
                {
                    maxCountSeq++;
                }
                if (C[i][j] > 0)
                {
                    maxCountParallel++;
                }
            }
        }

        printf("      %.6f", speedup);
        printf("  %.6f   %-5d                %-5d \n", efficiency, maxCountSeq, maxCountParallel);

        // Verify results
        int correct = 1;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (B[i][j] != C[i][j])
                {
                    correct = 0;
                    break;
                }
            }
            if (!correct)
                break;
        }

        if (!correct)
        {
            printf("\nError in calculation\n");
        }

        if (rows <= 14 && cols <= 14)
        {
            printf("\nOriginal Array (A):\n");
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    printf("%3d ", A[i][j]);
                }
                printf("\n");
            }
            printf("\nLocal Max Array (B):\n");
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (B[i][j] == 0)
                        printf("-- ");
                    else
                        printf("%3d ", B[i][j]);
                }
                printf("\n");
            }

            printf("\nLocal Max Array (C):\n");
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < cols; j++)
                {
                    if (C[i][j] == 0)
                        printf("-- ");
                    else
                        printf("%3d ", C[i][j]);
                }
                printf("\n");
            }
        }

        for (int i = 0; i < rows; i++)
        {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }

        free(A);
        free(B);
        free(C);
    }

    return 0;
}
