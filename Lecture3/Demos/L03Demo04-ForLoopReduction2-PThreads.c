#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 4

typedef struct {
    int *array;
    int start;
    int end;
    int partial_sum;
} ThreadData;

pthread_mutex_t mutex;
int global_sum = 0;

void *sum_array(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    pthread_t thread_id = pthread_self();

    data->partial_sum = 0;
    for (int i = data->start; i < data->end; i++) {
        data->partial_sum += data->array[i];
        pthread_mutex_lock(&mutex);
        global_sum += data->array[i];
        printf("\nTask %d, local sum=%d ,global sum = %d", (unsigned long)thread_id, data->partial_sum, global_sum);

        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main() {
    srand(time(0));
    int N = 10;
    int *A = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        A[i] = rand() % 10;

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    pthread_mutex_init(&mutex, NULL);

    int chunk_size = N / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].array = A;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, sum_array, (void *)&thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&mutex);

    printf("\n========================================\n");
    for (int i = 0; i < N; i++)
        printf("%d  ", A[i]);
    printf("\nSum = %d\n", global_sum);

    free(A);
    return 0;
}
