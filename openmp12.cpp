/*
    barrier : makes all threads wait until every thread reaches that point.
    =======================================================================

    Think of it as a meeting point : 
    Thread 0 ────────┐
    Thread 1 ────────┤
    Thread 2 ────────┼──> BARRIER ──> continue
    Thread 3 ────────┘
    The fastest thread waits for the slowest one.

    
*/

#include <iostream>
#include <omp.h>
#include <unistd.h>

using namespace std;

int main(){

    #pragma omp parallel num_threads(4)
    {
        int id = omp_get_thread_num();
        cout<<"Thread : "<<id<<"reached Phase 1\n";

        if(id==2){
            sleep(2);
        }

        #pragma omp barrier
        cout<<"Thread "<<id<<" passed the barrier\n";
    }
    return 0;
}