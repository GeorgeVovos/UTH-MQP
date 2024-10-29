#include <stdio.h>

int main()
{
    printf("In PThreads, you have to manually implement the scheduling strategy that resembles schedule(static)\n");
    printf("This involves calculating the range of iterations each thread should handle based on the total number of iterations and the number of threads.\n");
    return 0;
}
