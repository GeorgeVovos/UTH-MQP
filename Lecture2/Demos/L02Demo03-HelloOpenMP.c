#include <stdio.h>
#include <omp.h>

int main() {
   
   # pragma omp parallel
   {
      if(omp_get_thread_num() == 0 )
      {
         int P =  omp_get_num_threads();
         printf("Total number of tasks: %d \n", P);
      }

      printf("Hello from task %d of %d \n",omp_get_thread_num(), omp_get_num_threads());
      if ( omp_get_thread_num () == 2)
            printf("\t but me, task %d , greet you again one more time \n", omp_get_thread_num());
     
   }

   return 0;
}
