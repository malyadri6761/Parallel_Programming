/*
    schedule(dynamic) - This is the natural comparision to schedule(static).

    schedule(dynamic,2) - Give each thread 2 iterations at a time. 
                          When a thread finishes its 2 iterations, it gets another 2.
    Chunk 1 → 0, 1
    Chunk 2 → 2, 3
    Chunk 3 → 4, 5
    Chunk 4 → 6, 7
    Chunk 5 → 8, 9
    ...

    Important Point : A thread doesn't permanently own a fixed range of iterations.


    ============================
    ||  Static vs Dynamic     ||
    ============================

    Static : #pragma omp parallel for schedule(static)
    ==================================================
    Approximately:
        T0 → 0  1  2  3  4
        T1 → 5  6  7  8  9
        T2 → 10 11 12 13 14
        T3 → 15 16 17 18 19
    Assignment happens ahead of time.
    
    Dynamic : #pragma omp parallel for schedule(dynamic)
    ====================================================
        T0 → 0  1 → gets another chunk
        T1 → 2  3 → gets another chunk
        T2 → 4  5 → gets another chunk
        T3 → 6  7 → gets another chunk
    A thread that finishes early can take more work.

    Q) Why do we need dynamic?
    Ans : Some iterations are cheap and Some iterations are expensive.
    
    Imagine
    ========
    Iteration cost:

    0  → █
    1  → █
    2  → █████████
    3  → █
    4  → █████████████
    5  → █
    ...

    With static:
    ===========
    T0 → cheap cheap EXPENSIVE
    T1 → cheap EXPENSIVE cheap
    T2 → cheap cheap cheap
    T3 → EXPENSIVE cheap cheap

    Some threads may finish much earlier than others.
    That's called load imbalance.

    With Dynamic:
    =============
    Finished threads to take additional work:
              Work Queue
       ┌───────────────┐
       │  iteration    │
       │  iteration    │
       │  iteration    │
       │  iteration    │
       └───────────────┘
          ↑       ↑
         T0       T1
       requests requests
        work      work

    But Dynamic has a cost:
    ======================
    Dynamic scheduling requires OpenMP to manage the work distribution.
    Therefore : 
        static
            ↓
        lower scheduling overhead
            ↓
        usually faster when work is uniform
    
    While : 
        dynamic
            ↓
        higher scheduling overhead
            ↓
        better load balancing when work varies
    
    So, Rule is :
    ==========================================================
    | Workload                           | Schedule          |
    | ---------------------------------- | ----------------- |
    | Every iteration similar            | `static`          |
    | Iterations have different costs    | `dynamic`         |
    | Need very fine-grained balancing   | `dynamic, 1`      |
    | Want to reduce scheduling overhead | Larger chunk size |
    ==========================================================
*/

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;
int main(){

    const int N = 20;

    vector<int> A(N);
    vector<int> B(N);
    vector<int> C(N);
   
    for(int i=0;i<N;i++){
        A[i] = i;
        B[i] = 2*i;
    }

    #pragma omp parallel for schedule(dynamic,2)
    for(int i=0;i<N;i++){
        int thread_id = omp_get_thread_num();

        C[i] = A[i]+ B[i];
        printf("Thread %d -> i = %d ->C[%d] = %d\n",thread_id,i,i,C[i]);
    }

    cout<<"\n Final array : \n";

    for(int i=0;i<N;i++){
        cout<<C[i]<<" ";
    }
    cout<<endl;
    return 0;
}