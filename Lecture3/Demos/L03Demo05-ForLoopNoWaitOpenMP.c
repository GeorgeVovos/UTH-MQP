#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
    srand(time(0));
    int N = 100;
    int sum = 0;
    int i;
    int *A = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
      A[i] = rand() % 10;
    
//  #pragma omp parallel for private(i) shared(N) reduction(+:sum) nowait DOESN'T COMPILE
    #pragma omp parallel private(i) shared(N)
    {
        #pragma omp for reduction(+:sum) nowait
        for (int i = 0; i < N; i++)
        {
            sum += A[i];
            printf("\nTask %d, i =%d, sum=%d",omp_get_thread_num(), i , sum);
        }
    }

    printf("\n========================================");
    printf("\n");
    for (i = 0; i < N; i++)
        printf("%d  ",A[i]);
   
    printf("\n");
    printf("Sum = %d  ",sum);

    return 0;
}
