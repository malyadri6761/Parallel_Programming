/*
    Padding
    =======
    One way to reduce false sharing is to separate the variable.
    Conceptually
    ============
    Without padding:

    T0 T1 T2 T3
    │  │  │  │
    └──┴──┴──┴── same cache line


    With padding:

    T0              T1              T2              T3
    │               │               │               │
    cache line      cache line      cache line      cache line


*/
#include <iostream>
#include <omp.h>

using namespace std;

struct Counter{
    long long value;
    char padding[56];
};

int main(){
    Counter counter[4] = {0};
    double start = omp_get_wtime();

    #pragma omp parallel for num_threads(4)
    for(int i=0;i<4;i++){
        for(long long j=0;j<100000000;j++){
            counter[i].value++;
        }
    }
    double end = omp_get_wtime();
    cout<<"Time = "<<end-start<<" seconds\n";
    return 0;
}

/* 
    The padding increases the spacing between counters, making it much less likely that
    different threads repeadly invalidate each other's cache lines.

    Important Distinction
    =====================
    False sharing is not a race condition.

    Race Condition
    ==============
    Two threads access the same variable concurrently, with at least one write.
    Thread 0 ──┐
               ├── sum
    Thread 1 ──┘

    False Sharing
    =============
    Threads access different variables, but those variables happen to occupy the same cache
    line.
    Thread 0 → data[0] ┐
                       ├── same cache line
    Thread 1 → data[1] ┘

    Race Condition = Correctness Problem
    False Sharing = Performance Problem

*/