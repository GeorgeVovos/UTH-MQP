#include <stdio.h>
#include <omp.h>

int main()
{
    int N = 40;
    int i;
    #pragma omp parallel shared(N) private(i)
    {
        #pragma omp for
        for (i = 0; i < N; i++)
            printf("\n Task %d : runs %d of loop...", omp_get_thread_num(), i);
    }

    return 0;
}
