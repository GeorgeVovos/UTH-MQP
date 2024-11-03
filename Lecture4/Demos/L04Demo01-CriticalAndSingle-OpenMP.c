#include <stdio.h>
#include <omp.h>

int main()
{

    int a=0, b=0;
    #pragma omp parallel
    {
        #pragma omp critical
        a++;

        #pragma omp single
        b++;

    }

    printf("a=%d, b=%d \n", a,b);
    
    return 0;
}
