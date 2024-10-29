# University of Thessaly - 2024 Ms Software Engineering for Internet & Mobile Applications
## Multicore and quantum programming demos and exercises

## Setup

The codes sample work on both Windows and Linux.   
You just need a C compiler for your OS.    
Don't forget the "-fopenmp" flag when compiling a file    
e.g
`gcc.exe -fopenmp -g Filename.c`

## References/Bibliography
- [Programming Your GPU with OpenMP 2023](https://mitpress.mit.edu/9780262547536/programming-your-gpu-with-openmp/) 
   Source code can be found [here](https://github.com/tomdeakin/programming-gpu-openmp)
- [The OpenMP Common Core Making OpenMP Simple Again 2019](https://mitpress.mit.edu/9780262538862/the-openmp-common-core/)
- [Using OpenMP—The Next Step: Affinity, Accelerators, Tasking, and SIMD 2017](https://direct.mit.edu/books/monograph/4482/Using-OpenMP-The-Next-StepAffinity-Accelerators)

- https://www.cs.cmu.edu/afs/cs/academic/class/15492-f07/www/pthreads.html
- https://docs.oracle.com/cd/E26502_01/html/E35303/tlib-1.html
- https://randu.org/tutorials/threads/


    

## Differences Between OpenMP and PThreads

OpenMP and PThreads are both popular parallel programming libraries but differ significantly in their abstraction level, usage, and capabilities.

### 1. Abstraction Level
- **OpenMP**: High-level API, providing a simpler and more abstract approach to parallelism. It uses compiler directives to manage parallel execution, making it easier for developers to implement multi-threaded code without directly managing threads.
- **PThreads**: Low-level API, requiring explicit thread management by the programmer. It provides finer control over thread creation, synchronization, and communication but requires more boilerplate code and careful handling of concurrency.

### 2. Ease of Use
- **OpenMP**: Easier to use and less error-prone due to its high-level constructs (`#pragma` directives). Adding parallelism often involves minimal code changes.
- **PThreads**: More complex and error-prone since it requires direct handling of threads, mutexes, and other synchronization primitives.

### 3. Platform Dependency
- **OpenMP**: Cross-platform and primarily intended for shared-memory parallelism on CPUs.
- **PThreads**: POSIX standard, mainly used on UNIX-like systems (Linux, macOS), though some Windows libraries provide partial support.

### 4. Parallelism Model
- **OpenMP**: Supports only shared-memory parallelism, making it ideal for multi-threading on shared-memory architectures.
- **PThreads**: Primarily used for shared-memory parallelism but can be combined with other techniques to implement distributed memory models.

### 5. Performance Control
- **OpenMP**: Generally incurs more overhead due to its abstraction, but allows thread control through `#pragma` settings.
- **PThreads**: Offers better performance tuning at a granular level due to direct control of thread behavior, synchronization, and resource management.

In summary, OpenMP is best suited for high-level, simpler parallel programming, while PThreads is better suited for applications needing low-level thread control and portability across POSIX-compliant systems.


## Algorithm for Converting a C Program from OpenMP to PThreads

Converting an OpenMP program to use PThreads involves replacing OpenMP directives with explicit thread management and synchronization. The following steps outline a general algorithm for this process:

### 1. Identify Parallel Regions
   - Locate regions in the code where `#pragma omp parallel` and `#pragma omp parallel for` are used.
   - For each identified region, plan to create a new thread function that will handle the parallel workload.

### 2. Define Thread Function
   - Create a function that will serve as the target for each PThread. This function should:
     - Take a single `void *` argument (as required by `pthread_create`).
     - Contain the code that was in the OpenMP parallel region, adapted to execute only the relevant part of the work for each thread.

### 3. Divide Work Among Threads
   - Replace `#pragma omp parallel for` loops by dividing the loop range across threads manually.
   - Calculate each thread’s workload range based on the thread index (e.g., `start` and `end` values).
   - Store thread-specific data (like start and end indices) in a structure and pass a pointer to this structure to each thread.

### 4. Replace OpenMP Reduction and Synchronization
   - For OpenMP reduction operations (e.g., `reduction(+:sum)`), create a global or shared variable and protect access to it using a `pthread_mutex` or other synchronization mechanisms.
   - Where `#pragma omp critical` or `#pragma omp atomic` are used, replace them with `pthread_mutex_lock` and `pthread_mutex_unlock` around critical sections.

### 5. Initialize and Create Threads
   - Initialize an array of `pthread_t` variables to hold thread IDs.
   - For each thread, use `pthread_create` to start execution of the thread function, passing in the necessary data (e.g., workload boundaries).
   - Ensure each thread handles only its designated portion of the workload.

### 6. Synchronize and Join Threads
   - After launching all threads, use `pthread_join` on each thread to ensure that all threads complete before proceeding.
   - This replaces OpenMP’s implicit synchronization at the end of a parallel region.

### 7. Cleanup Resources
   - If mutexes or other synchronization objects are used, release them (e.g., using `pthread_mutex_destroy`).
   - Free dynamically allocated memory, if any, to avoid memory leaks.

### Example Summary
The converted PThread-based program should:
   - Use `pthread_create` to launch threads.
   - Manage data access explicitly with mutexes where needed.
   - Use custom logic to divide workloads across threads.

Following these steps ensures a structured transition from OpenMP to PThreads, preserving parallelism while accommodating the lower-level thread management in PThreads.
