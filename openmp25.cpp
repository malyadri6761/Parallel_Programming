/*
    Thread Affinity
    ===============
    Contorlling or understanding which CPU cores OpenMP threads run on.
    This matters because moving a thread between CPU cores can hurt cache locality.

    Q) Why CPU core placement matters
    Ans : Suppose you have 4 CPU cores : 
    
    Core 0    Core 1    Core 2    Core 3
      │         │         │         │
      T0        T1        T2        T3
    
    Ideally, each thread stays on a suitable CPU core.
    If the operating system repreatedly moves a thread : 
        T0 → Core 0
               ↓
             Core 2
               ↓
             Core 1
    The thread may lose useful data from its previous core's cache.
  
    
OpenMP Environment Variables
============================
OMP_NUM_THREADS
OMP_PROC_BIND - controls wheter OpenMP threads are bound to particular processor places.
OMP_PLACES - Speficy the processor places.

Ex: 
==
    OMP_NUM_THREADS = "4"
    OMP_PLACES = "cores"
    OMP_PROC_BIND = "true"

    This asks the OpenMP runtime to use processor cores as places and bind threads
    accordingly.
    

*/
#include <iostream>
#include <omp.h>

int main() {

    #pragma omp parallel num_threads(4)
    {
        int thread_id = omp_get_thread_num();
        int place = omp_get_place_num();

        printf("Thread %d -> place %d\n",
               thread_id, place);
    }

    return 0;
}