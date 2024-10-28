#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 4 

void* print_thread_number(void *arg) {
    pthread_t thread_id = pthread_self();
    printf("Thread Number: %ld \n", (unsigned long)thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[MAX_THREADS]; 

    for (long t = 0; t < MAX_THREADS; t++) {

        int threadId = pthread_create(&threads[t], NULL, print_thread_number, NULL);
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
