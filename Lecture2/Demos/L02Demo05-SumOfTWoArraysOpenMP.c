#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <stdlib.h>
#define N 5

int main() {
   srand(time(0));

   int *A = malloc(N * sizeof(int));
   int *B = malloc(N * sizeof(int));
   int *C = malloc(N * sizeof(int));


   for (int i = 0; i < N; i++)
   {
      A[i] = rand() % 10;
      B[i] = rand() % 10;
   }

   #pragma omp parallel for
   for (int i =0; i <N; i++)
      C[i] = A[i] + B[i];


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
      
   return 0;
}
