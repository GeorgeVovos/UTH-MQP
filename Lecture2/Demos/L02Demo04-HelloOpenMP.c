#include <stdio.h>
#include <omp.h>

int main() {
   
   int totalNumberOfTasks;
   int currentTaskNumber;

   # pragma omp parallel private(currentTaskNumber)
   {
      currentTaskNumber = omp_get_thread_num();
      printf("Hello World from task %d \n", currentTaskNumber);

      if(currentTaskNumber == 0) { 
         totalNumberOfTasks = omp_get_num_threads();
         printf("Total number of tasks= %d \n", totalNumberOfTasks);
      }
   }

   return 0;
}
