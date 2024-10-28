#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
    srand(time(0));
    int N = 5;
    int sum = 0;

    int *A = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
      A[i] = rand() % 10;
    
    #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < N; i++)
            sum += A[i];
    
    printf("========================================");
    printf("\n");
    for (int i = 0; i < N; i++)
        printf("%d  ",A[i]);
   
    printf("\n");
    printf("Sum = %d  ",sum);

    return 0;
}
