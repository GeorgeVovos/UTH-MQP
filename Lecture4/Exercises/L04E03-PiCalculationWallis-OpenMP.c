#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    long arrayLengths[] = {300,2000000, 400000000, 800000000, 1600000000};
    int iterationCount = sizeof(arrayLengths) / sizeof(long);

    srand(time(0));

    printf("Iterations:%d  , No of threads %d\n", iterationCount, omp_get_max_threads());
    printf("Size        Sequential(s)   Parallel(s)   Speedup   Efficiency Pi(Seq)             Pi(Parallel)\n");
    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++)
    {
        long currentDataLength = arrayLengths[currentIteration];

        // Sequential logic
        double sequential_start_time = omp_get_wtime();
       
        double pi_sequential = 1.0;
        for (int i = 1; i <= currentDataLength; i++) {
              pi_sequential *= (4.0 * i * i) / (4.0 * i * i - 1);
        }
        
        pi_sequential *= 2;


        double sequential_end_time = omp_get_wtime();
        double sequential_elapsed_time = sequential_end_time - sequential_start_time;

        printf("%010ld  %.6f", currentDataLength, sequential_elapsed_time);

        // Parallel logic
        double parallel_start_time = omp_get_wtime();
        int parallel_i;
        
        double piParallel = 1.0;
        #pragma omp parallel for reduction(*:piParallel)
        for (int i = 1; i <= currentDataLength; i++) {
              piParallel *= (4.0 * i * i) / (4.0 * i * i - 1);
        }
        
        piParallel *= 2;

        double parallel_end_time = omp_get_wtime();
        double parallel_elapsed_time = parallel_end_time - parallel_start_time;

        printf("        %.6f", parallel_elapsed_time);

        // End of Parallel logic

        double speedup = sequential_elapsed_time / parallel_elapsed_time;
        double efficiency = speedup / omp_get_max_threads();
        printf("      %.6f", speedup);
        printf("  %.6f   %.15f   %.15f", efficiency , pi_sequential , piParallel );
        printf("\n");

    }

    return 0;
}
