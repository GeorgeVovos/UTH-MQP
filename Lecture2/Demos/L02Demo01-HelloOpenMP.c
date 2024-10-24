#include <stdio.h>
#include <omp.h>

int main() {
   
   #pragma omp parallel
   printf("Thread Number:%d \n",omp_get_thread_num());

   return 0;
}