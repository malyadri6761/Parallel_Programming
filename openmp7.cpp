/*
    Data sharing : Shared, Private, FirstPrivate
    ============================================
    This is important because multiple threads need to know which
    variables they share and which variables each thread gets its own copy of.
*/

#include <iostream>
#include <omp.h>

using namespace std;

int main(){
    int x = 10;


    /*
    

    Shared 
    =======
    A shared variable has one copy accessible by all threads.
                     x = 10
                    │
        ┌───────────┼───────────┐
        ↓           ↓           ↓
       T0          T1          T2
        │           │           │
        └────── same x ─────────┘

    All threads access the same memory location.
    */
   /*
    #pragma omp parallel shared(x)
    {
        int tid = omp_get_thread_num();
        cout<<"Thread "<<tid<<" sees x = "<<x<<endl;
    }
    */

    /*
    Private
    =======
    Every thread gets its own separate copy.
    Original x = 10

          private(x)
              │
     ┌────────┼────────┐
     ↓        ↓        ↓
    T0       T1       T2
   x=0      x=100    x=200

   Each thread has it's own x.
   Important : The original x outside the parallel region is not modified
   these private copies.
    */

   /*
    #pragma omp parallel private(x)
    {
        int tid = omp_get_thread_num();
        x = tid*100;
        cout<<"Thread "<< tid<< "-> x = "<<x<<endl;
    }
    */
   
    /*
    firstprivate
    ============
    firstprivate is similar to private, but each thread's private copy 
    is initialized with the original value.
                    Original
                 x = 10
                   │
          ┌────────┼────────┐
          ↓        ↓        ↓
         T0       T1       T2
        x=10     x=10     x=10
          ↓        ↓        ↓
        x=10     x=11     x=12
   */
   #pragma omp parallel firstprivate(x)
   {
        int tid = omp_get_thread_num();
        x = x+ tid;
        cout<<" Thread "<<tid << "-> x = "<< x << endl;
   }
    return 0;
}


/*
    Difference 
    ==========

    | Type           | Copies              | Initial value                                  |
    | -------------- | ------------------- | ---------------------------------------------- |
    | `shared`       | One shared copy     | Original variable                              |
    | `private`      | One copy per thread | Uninitialized/undefined for ordinary variables |
    | `firstprivate` | One copy per thread | Initialized from original                      |

*/