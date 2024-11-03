#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int main()
{
    long arrayLengths[] = {30000,2000000, 400000000, 800000000, 1600000000};
    int iterationCount = sizeof(arrayLengths) / sizeof(long);

    srand(time(0));

    printf("Iterations:%d  , No of threads %d\n", iterationCount, omp_get_max_threads());
    printf("Size        Sequential(s)   Parallel(s)   Speedup   Efficiency Pi(Seq)         Pi(Parallel)\n");
    for (int currentIteration = 0; currentIteration < iterationCount; currentIteration++)
    {
        long currentDataLength = arrayLengths[currentIteration];

        // Sequential logic
        double sequential_start_time = omp_get_wtime();
       
        double pi_sequential = 0.0;
        int sign_Sequential = 1;
        for (long long int k = 0; k < currentDataLength; k++) {
            pi_sequential += sign_Sequential * (1.0 / (2 * k + 1));
            sign_Sequential = -sign_Sequential; 
        }

        pi_sequential *= 4;


        double sequential_end_time = omp_get_wtime();
        double sequential_elapsed_time = sequential_end_time - sequential_start_time;

        printf("%010ld  %.6f", currentDataLength, sequential_elapsed_time);

        // Parallel logic
        double parallel_start_time = omp_get_wtime();
        int parallel_i;
        
        double pi_Parallel = 0.0;
      
        #pragma omp parallel for reduction(+:pi_Parallel)
        for (long long int k = 0; k < currentDataLength; k++) {
            pi_Parallel += (k % 2 == 0 ? 1.0 : -1.0) / (2 * k + 1);
        }

        pi_Parallel*= 4;

        double parallel_end_time = omp_get_wtime();
        double parallel_elapsed_time = parallel_end_time - parallel_start_time;

        printf("        %.6f", parallel_elapsed_time);

        // End of Parallel logic

        double speedup = sequential_elapsed_time / parallel_elapsed_time;
        double efficiency = speedup / omp_get_max_threads();
        printf("      %.6f", speedup);
        printf("  %.6f   %.15f   %.15f", efficiency , pi_sequential , pi_Parallel );
        printf("\n");

    }

    return 0;
}
