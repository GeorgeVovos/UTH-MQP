#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main()
{
    srand(time(0));
    int N = 5;
    int x=1;
    int i;
    int *A = malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
      A[i] = rand() % 10;
    
   #pragma omp parallel for private(i) shared(N) reduction(*:x)
        for (int i = 0; i < N; i++)
        {
            x *= A[i];
        }
  
    printf("\n========================================");
    printf("\n");
    for (i = 0; i < N; i++)
        printf("%d  ",A[i]);
   
    printf("\n");
    printf("Product = %d  ",x);

    return 0;
}
