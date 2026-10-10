/*
    ================================
    || Race Conditions in OpenMP. ||
    ================================

    A race condition occurs when multiple threads access and modify the same shared
    variable at the same time, and the final result depends on the timing of the threads.

    Consider :
    =========
    int sum = 0;

    #pragma omp parallel for
    for (int i = 0; i < 1000; i++) {
        sum++;
    }
    
    Excepted Result : sum = 1000
    ===============
    But the result can be smaller.

    Why?
    ====
    sum++ is actually multiple operations.
    READ sum
    ↓
    ADD 1
    ↓
    WRITE sum

    Suppose
    =======
    Thread 0                 Thread 1

    read sum = 10
                            read sum = 10

    add 1                    add 1

    write 11
                            write 11

    Two increments happend, but the result is : 11 instead of 12 one update was lost.


*/

/*
#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    int sum = 0;

    omp_set_num_threads(4);

    #pragma omp parallel for
    for(int i=0;i<100000;i++)
        sum++;
    cout<<"Expected : 100000\n";
    cout<<"Actual : "<<sum<<"\n";
    return 0;
}
    Expected : 100000
    Actual : 32675
*/

/*
    How do we fix it?
    =================
    OpenMP provides several synchronization mechanisms.
    The major ones you'll learn are : 

    Race condition
      │
      ├── critical
      │
      ├── atomic
      │
      └── reduction
    
    For this particular problem, the best solution is usually reduction : 
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < 100000; i++) {
        sum++;
    }
     
    Conceptually :
    =============
              sum = 0
             │
       ┌─────┼─────┐
       ↓     ↓     ↓
      T0    T1    T2    T3
     local local local local
      sum   sum   sum   sum
       │     │     │     │
       └─────┴─────┴─────┘
               ↓
        combine the results
               ↓
          final sum

    Important Distinction : 
    ======================
    Don't think : Parallel code is automatically safe.
    Instead : Parallel threads sharing mutable data require shynchronization 
    or a suitable parallel pattern.
*/