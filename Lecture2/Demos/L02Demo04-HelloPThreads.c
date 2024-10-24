#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 7

typedef struct {
    int thread_num;
    int total_num_threads;
} thread_data_t;


void* thread_function(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    int currentTaskNumber = data->thread_num;

    printf("Hello World from task %d \n", currentTaskNumber);

    if (currentTaskNumber == 0) {
        printf("Total number of tasks = %d \n", data->total_num_threads);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_THREADS]; 
    thread_data_t thread_data[MAX_THREADS];

    for (long t = 0; t < MAX_THREADS; t++) {
        thread_data[t].thread_num = t; 
        thread_data[t].total_num_threads = MAX_THREADS;

        int threadId = pthread_create(&threads[t], NULL, thread_function, (void*)&thread_data[t]);
        if (threadId) {
            printf("Error: unable to create thread, %d\n", threadId);
            return -1;
        }
    }

    for (long t = 0; t < MAX_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    return 0;
}
