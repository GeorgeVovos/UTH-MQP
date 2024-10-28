#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
    srand(time(0));
    int N = 10;
    int sum = 0;
    int i;
    int *A = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
      A[i] = rand() % 10;
    
    #pragma omp parallel private(i) shared(N)
    {
        #pragma omp for
        for (int i = 0; i < N; i++)
            sum += A[i];
        
        #pragma omp for nowait
        for (int i = 0; i < N; i++)
            sum += A[i];
    }

    printf("\n========================================");
    printf("\n");
    for (i = 0; i < N; i++)
        printf("%d  ",A[i]);
   
    printf("\n");
    printf("Sum = %d  ",sum);

    return 0;
}
