#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 300

int main() {

    srand(time(0));
   
    int A[N][N], B[N][N], C1[N][N], C2[N][N];

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }
    
    double sequential_start_time = omp_get_wtime();
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C1[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C1[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double sequential_end_time = omp_get_wtime();
    printf("Sequential time: %f\n", sequential_end_time - sequential_start_time);

    double parallel_start_time = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C2[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C2[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    double parallel_end_time = omp_get_wtime();
    printf("Parallel time with collapse(2): %f\n", parallel_end_time - parallel_start_time);


    //Validation
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if(C1[i][j] != C2[i][j])
            {
                printf("There is an error in the calculation\n");
            }
        }
    }

    return 0;
}