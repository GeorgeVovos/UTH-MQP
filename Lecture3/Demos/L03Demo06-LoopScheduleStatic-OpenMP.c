#include <stdio.h>
#include <omp.h>

int main()
{
    int N = 100;
    int i;
    #pragma omp parallel for schedule(static) shared(N) private(i)
        for (i = 0; i < N; i++)
            printf("\n Task %d : runs %d of loop...", omp_get_thread_num(), i);
    
    return 0;
}
