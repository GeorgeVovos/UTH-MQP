#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
    srand(time(0));
    int N = 5;
    int sum = 0;
    int i;
    int *A = malloc(N * sizeof(int));
    int *B = malloc(N * sizeof(int));
    int *C = malloc(N * sizeof(int));
    int *D = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
    {
       B[i] = rand() % 10;
       D[i] = rand() % 10;
    }

    #pragma omp parallel default(none) shared(N, A, B, C, D, sum) private(i)
    {
        #pragma omp for nowait
        for (i = 0; i < N; i++)
             A[i]= 10 + B[i];
        
        #pragma omp for nowait
        for (i = 0; i < N; i++)
            C[i]= 10 + D[i];

        #pragma omp barrier

        #pragma omp for nowait reduction(+:sum)
        for (int i = 0; i < N; i++)
            sum += A[i]+C[i];
    }

    printf("\n========================================");
    printf("\n");
    for (i = 0; i < N; i++)
        printf("%d  ",A[i]);
   
    printf("\n");
    for (i = 0; i < N; i++)
        printf("%d  ",C[i]);

    printf("\n");
    printf("Sum = %d  ",sum);

    return 0;
}
