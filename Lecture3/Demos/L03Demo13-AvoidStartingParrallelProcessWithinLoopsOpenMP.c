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
  
    for (int i = 0; i < N; i++)
    {
       A[i] = rand() % 10;
       B[i] = rand() % 10;
    }

    //AVOID THIS AS THE OVERHEAD OF THE PARALLELISM IS HIGH
    for (int i = 0; i < N; i++)
        for (int j   = 0; j < N; j++)
        {
            #pragma omp parallel for
            for (int k=0; k<N; k++)
            {
                //Do something
            }
        }
    
    
    //THIS IS MUCH BETTER THAN THE ABOVE
    #pragma omp parallel
    {
        for (int i = 0; i < N; i++)
            for (int j   = 0; j < N; j++)
            {
                #pragma omp for
                for (int k=0; k<N; k++)
                {
                    //Do something
                }
            }
    }

    return 0;
}
