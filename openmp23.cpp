/*
    False Sharing
    =============

    False sharing is a CPU cache performance problem. It is important before moving to
    CUDA you how memory access affects parallel performance.

    Basic Idea
    ==========
    Four threads update different variables.
    Thread 0 → data[0]
    Thread 1 → data[1]
    Thread 2 → data[2]
    Thread 3 → data[3]

    You migh think there is no conflict because they use different elements.
    But CPUs don;t normally transfoer memory one integer at a time. they use cache lines, 
    commonly 64 bytes on modern CPUs.

    Conceptually:
    ============
    Cache line
    ┌────┬────┬────┬────┬────┬────┬────┬────┐
    │ x0 │ x1 │ x2 │ x3 │ x4 │ x5 │ x6 │ x7 │
    └────┴────┴────┴────┴────┴────┴────┴────┘
    ↑    ↑
    T0   T1

    Even though Thread 0 and Thread 1 modify different variable, they may be modifying
    data in the same cache line.


    Why is that bad?
    ================
    Each CPU core has its own cache.

    Imagine : 
    =========
    Core 0                  Core 1
    Cache                   Cache
    │                       │
    └── data[0]             └── data[1]

    If both values are on the same cache line, when Thread 0 modifier data[0], the cache-
    coherence symste may invaildate the corresponding cache line in core 1.

    Then Thread 1 modifies data[1], causing the opposite effect.

    Conceptually:
    =============
    Core 0 modifies data[0]
            ↓
    cache line changes
            ↓
    Core 1's copy becomes invalid
            ↓
    Core 1 modifies data[1]
            ↓
    Core 0's copy becomes invalid
            ↓
    repeat...

    The threads aren't logically sharing the same variable, but the hardware is repreatedly
    moving/invalidation the same cache line.
    That's false sharing.

*/
#include <iostream>
#include <omp.h>

using namespace std;

int main(){

    const int N = 4;
    long long counter[N] = {0};

    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(4)
    for(int i=0;i<N;i++){
        for(long long j=0;j<1000000;j++){
            counter[i]++;
        }
    }
    double end = omp_get_wtime();
    cout<<"Time = "<<end-start<<" seconds\n";
    return 0;
}
/*
    Each thread has a different
    Thread 0 → counter[0]
    Thread 1 → counter[1]
    Thread 2 → counter[2]
    Thread 3 → counter[3]
    But these integers are probably stored close together:
    counter[0] counter[1] counter[2] counter[3]
    and therefore may share a cache line.

    
*/