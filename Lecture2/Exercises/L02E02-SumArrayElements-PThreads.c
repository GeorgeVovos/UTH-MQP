#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define MAX_THREADS 4 // Define the number of threads

typedef struct {
    int *A;
    long start;
    long end;
    long long partial_sum; // Store the sum computed by each thread
} ThreadData;

// Mutex for synchronizing updates to the global sum
pthread_mutex_t sum_mutex;
long long global_parallel_sum = 0; // Global sum to be updated by threads

// Function to be executed by each thread
void *parallel_sum(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    long long local_sum = 0;

    for (long i = data->start; i < data->end; i++) {
        local_sum += data->A[i];
    }

    // Update the global sum with the local sum (critical section)
    pthread_mutex_lock(&sum_mutex);
    global_parallel_sum += local_sum;
    pthread_mutex_unlock(&sum_mutex);

    data->partial_sum = local_sum; // Store the partial sum
    pthread_exit(NULL);
}

int main() {

    long arrayLengths[] = {2000000, 20000000, 200000000, 2000000000};
    int iterationCount = sizeof(arrayLengths) / sizeof(long);

    srand(time(0));

    printf("Iterations: %d  , No of threads: %d\n", iterationCount, MAX_THREADS);
    printf("Size          Sequential(s)   Parallel(s)   Speedup   Efficiency\n");

    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++) {
        long currentDataLength = arrayLengths[currentIteration];

        int *A = malloc(currentDataLength * sizeof(int));

        // Initialize array A with random values
        for (int i = 0; i < currentDataLength; i++) {
            A[i] = rand() % 1000000;
        }

        // Sequential logic
        double sequential_start_time = (double)clock() / CLOCKS_PER_SEC;
        long long sequential_sum = 0;
        for (int seq_i = 0; seq_i < currentDataLength; seq_i++) {
            sequential_sum += A[seq_i];
        }
        double sequential_end_time = (double)clock() / CLOCKS_PER_SEC;
        double sequential_elapsed_time = sequential_end_time - sequential_start_time;

        printf("%010ld    %.6f", currentDataLength, sequential_elapsed_time);

        // Parallel logic using PThreads
        pthread_t threads[MAX_THREADS];
        ThreadData thread_data[MAX_THREADS];

        long chunk_size = currentDataLength / MAX_THREADS;
        global_parallel_sum = 0; // Reset global sum
        pthread_mutex_init(&sum_mutex, NULL); // Initialize the mutex

        double parallel_start_time = (double)clock() / CLOCKS_PER_SEC;

        // Create threads
        for (int t = 0; t < MAX_THREADS; t++) {
            thread_data[t].A = A;
            thread_data[t].start = t * chunk_size;
            thread_data[t].end = (t == MAX_THREADS - 1) ? currentDataLength : (t + 1) * chunk_size;
            thread_data[t].partial_sum = 0;

            pthread_create(&threads[t], NULL, parallel_sum, (void *)&thread_data[t]);
        }

        // Join threads
        for (int t = 0; t < MAX_THREADS; t++) {
            pthread_join(threads[t], NULL);
        }

        double parallel_end_time = (double)clock() / CLOCKS_PER_SEC;
        double parallel_elapsed_time = parallel_end_time - parallel_start_time;

        printf("        %.6f", parallel_elapsed_time);

        // Calculate speedup and efficiency
        double speedup = sequential_elapsed_time / parallel_elapsed_time;
        double efficiency = speedup / MAX_THREADS;
        printf("      %.6f", speedup);
        printf("  %.6f", efficiency);

        // Check if the results match
        if (sequential_sum != global_parallel_sum) {
            printf("The outcomes don't match");
        }

        printf("\n");

        pthread_mutex_destroy(&sum_mutex); // Destroy the mutex
        free(A);
    }

    return 0;
}
