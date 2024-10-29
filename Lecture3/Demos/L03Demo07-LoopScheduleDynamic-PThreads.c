#include <stdio.h>

int main()
{
    printf("In PThreads, you have to manually implement the scheduling strategy that resembles schedule(dynamic)\n");
    printf("Implementing Dynamic Scheduling in PThreads\n");
    printf("\t1)Create a Shared Queue: Use a shared queue or a similar structure to hold available iterations that can be picked up by any thread that finishes its assigned work.\n");
    printf("\t2)Mutex for Synchronization: Use a mutex to ensure thread-safe access to the shared queue.\n");
    printf("\t3)Dynamic Work Assignment: After finishing its assigned work, a thread checks the queue for any remaining iterations and picks them up until there are no more iterations left.\n");
    return 0;
}
