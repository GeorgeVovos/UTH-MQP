#include <stdio.h>
#include <omp.h>

int main() {
   
   # pragma omp parallel
   {
      if(omp_get_thread_num() == 0 )
      {
         int P =  omp_get_num_threads();
         printf("Total number of tasks: %d \n\n", P);
         }
   }

   return 0;
}
