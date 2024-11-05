#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(0));

    int N = 5;
    int *A = malloc(N * sizeof(int));
    int *B = malloc(N * sizeof(int));

    // INIT
    for (int i = 0; i < N; i++)
    {
        A[i] = rand() % 10;
        B[i] = rand() % 10;
    }

    // Part 1
    double aValue = 0.0, bValue = 0.0, angle = 30.0;
    #pragma omp parallel for reduction(+ : aValue) reduction(+ : bValue)
    for (int parallel_i = 0; parallel_i < N; parallel_i++)
    {
        aValue += (A[parallel_i] * A[parallel_i]);
        bValue += (B[parallel_i] * B[parallel_i]);
    }

    aValue = sqrt(aValue);
    bValue = sqrt(bValue);
    double part1Result = aValue * bValue * cos(angle);

    // Part 2
    double eucleidianDistance = 0.0;
    double manhatanDistance = 0.0;

    #pragma omp parallel for reduction(+ : eucleidianDistance) reduction(+ : manhatanDistance)
    for (int parallel_i = 0; parallel_i < N; parallel_i++)
    {
        eucleidianDistance += (A[parallel_i] - B[parallel_i]) * (A[parallel_i] - B[parallel_i]);
        manhatanDistance += abs(A[parallel_i] - B[parallel_i]);
    }

    eucleidianDistance = sqrt(eucleidianDistance);

    // Part 3
    double w = 0;
    double nominatorSum = 0.0;
    double denominatorSum = 0.0;

    #pragma omp parallel for reduction(+ : nominatorSum) reduction(+ : denominatorSum)
    for (int parallel_i = 0; parallel_i < N; parallel_i++)
    {
        nominatorSum += (A[parallel_i] * B[parallel_i]);
        denominatorSum += B[parallel_i];
    }

    w = nominatorSum / denominatorSum;

    printf("Arrays\n");
    for (int i = 0; i < N; i++)
        printf("%d  ", A[i]);

    printf("\n");
    for (int i = 0; i < N; i++)
        printf("%d  ", B[i]);

    printf("\n");
    printf("\nPart 1 Result: %f", part1Result);
    printf("\nPart 2 eucleidianDistance: %f", eucleidianDistance);
    printf("\nPart 2 manhatanDistance : %f", manhatanDistance);
    printf("\nPart 3 w : %f", w);

    return 0;
}
