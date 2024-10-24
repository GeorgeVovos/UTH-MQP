#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 5
#define MAX_THREADS 2

typedef struct {
    int start;     
    int end;       
    int *A;        
    int *B;        
    int *C;       
} thread_data_t;

void* sum_arrays(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    
    for (int i = data->start; i < data->end; i++) {
        data->C[i] = data->A[i] + data->B[i];
    }

    pthread_exit(NULL);
}

int main() {
    srand(time(0));

    int *A = malloc(N * sizeof(int));
    int *B = malloc(N * sizeof(int));
    int *C = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }

    pthread_t threads[MAX_THREADS];
    thread_data_t thread_data[MAX_THREADS];
    int elements_per_thread = N / MAX_THREADS;

    for (int t = 0; t < MAX_THREADS; t++) {
        thread_data[t].start = t * elements_per_thread; 
        thread_data[t].end = (t == MAX_THREADS - 1) ? N : (t + 1) * elements_per_thread; 
        thread_data[t].A = A;
        thread_data[t].B = B;
        thread_data[t].C = C;

        int threadID = pthread_create(&threads[t], NULL, sum_arrays, (void*)&thread_data[t]);
        if (threadID) {
            printf("Error: unable to create thread, %d\n", threadID);
            exit(-1);
        }
    }

    for (int t = 0; t < MAX_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

   
   printf("========================================");
   printf("\n");
   for (int i = 0; i < N; i++)
      printf("%d  ",A[i]);
   
   printf("\n");
   for (int i = 0; i < N; i++)
      printf("%d  ",B[i]);
   
   printf("\n");
   for (int i = 0; i < N; i++)
      printf("%d  ",C[i]);
   
   free(A);
   free(B);
   free(C);

    return 0;
}
