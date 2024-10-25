#include <stdio.h>
#include <omp.h>
#define N 60
int main()
{

    #pragma omp parallel
    {
        #pragma omp for
        for (int i = 0; i < N; i++)
            printf("\n Task %d : runs %d of loop...", omp_get_thread_num(), i);
    }

    return 0;
}
