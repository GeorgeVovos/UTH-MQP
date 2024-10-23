#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <omp.h>
#define NUM_THREADS 28 // Adjust the number of threads as needed

typedef struct {
    int *A;
    double *B;
    int start;
    int end;
} thread_args;

void *thread_func(void *arg) {
    thread_args *args = (thread_args *)arg;
    int start = args->start;
    int end = args->end;
    for (int i = start; i < end; i++) {
        args->B[i] = 3.14159 * args->A[i];
    }
    pthread_exit(NULL);
}

int main() {
    long arrayLengths[] = {2000000, 20000000, 200000000, 400000000, 800000000, 1600000000};
    int iterationCount = sizeof(arrayLengths) / sizeof(long);
    pthread_t threads[NUM_THREADS];
    thread_args args[NUM_THREADS];

    srand(time(0));

    printf("Iterations: %d, No of threads %d\n", iterationCount, NUM_THREADS);
    printf("Size          Sequential(s)   Parallel(s)   Speedup   Efficiency\n");

    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++) {
        long currentDataLength = arrayLengths[currentIteration];

        int *A = malloc(currentDataLength * sizeof(int));
        double *B = malloc(currentDataLength * sizeof(double));

        for (int i = 0; i < currentDataLength; i++) {
            A[i] = rand() % 1000;
        }

        // Sequential logic
        double sequential_start_time = omp_get_wtime();
        for (int seq_i = 0; seq_i < currentDataLength; seq_i++) {
            B[seq_i] = 3.14159 * A[seq_i];
        }
        double sequential_end_time = omp_get_wtime();
        double sequential_elapsed_time = sequential_end_time - sequential_start_time;

        printf("%010ld    %.6f", currentDataLength, sequential_elapsed_time);

        // Parallel logic
        double parallel_start_time = omp_get_wtime();
        int chunk_size = currentDataLength / NUM_THREADS;
        for (int i = 0; i < NUM_THREADS; i++) {
            args[i].A = A;
            args[i].B = B;
            args[i].start = i * chunk_size;
            args[i].end = (i + 1) * chunk_size;
            if (i == NUM_THREADS - 1) {
                args[i].end = currentDataLength;
            }
            pthread_create(&threads[i], NULL, thread_func, (void *)&args[i]);
        }

        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }

        double parallel_end_time = omp_get_wtime();
        double parallel_elapsed_time = parallel_end_time - parallel_start_time;

        printf("        %.6f", parallel_elapsed_time);

        // End of Parallel logic
        double speedup = sequential_elapsed_time / parallel_elapsed_time;
        double efficiency = speedup / NUM_THREADS;
        printf("      %.6f", speedup);
        printf("  %.6f", efficiency);
        printf("\n");

        free(A);
        free(B);
    }

    return 0;
}