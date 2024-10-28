#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 6  


void* thread_function(void* threadId) {
    pthread_t thread_id = pthread_self();

    if (thread_id == 1) {
        printf("Total number of tasks: %d \n", MAX_THREADS);
    }

    printf("Hello from task %ld of %d \n", thread_id, MAX_THREADS);

    if (thread_id == 3) {
        printf("\tbut me, task %ld, greet you again one more time \n", thread_id);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_THREADS]; 
    for (long t = 0; t < MAX_THREADS; t++) {
        int threadId = pthread_create(&threads[t], NULL, thread_function, NULL);
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
